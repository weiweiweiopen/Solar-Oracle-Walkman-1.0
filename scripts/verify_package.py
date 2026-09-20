"""Validate published evidence and calculate energy assumptions from the exported netlist."""
from pathlib import Path
import collections, hashlib, json, math, re, shutil
import xml.etree.ElementTree as ET

root=Path(__file__).resolve().parents[1];hw=root/'hardware';verification=hw/'verification'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
drc=json.loads((verification/'drc.json').read_text());erc=json.loads((verification/'erc.json').read_text())
assert not drc['unconnected_items'] and not drc['schematic_parity']
assert not any(v['severity']=='error' for v in drc['violations'])
assert not any(sheet['violations'] for sheet in erc['sheets'])
assert {v['type'] for v in drc['violations']}=={'silk_over_copper'}
host=json.loads((root/'FIRMWARE_VERIFIED.json').read_text());assert host['host_startup_tests']=='passed'
shutil.copy2(root/'FIRMWARE_VERIFIED.json',verification/'firmware.json')
manifest_path=root/'build/source-manifest.json'
if not manifest_path.exists():manifest_path=verification/'design-sha256.json'
manifest=json.loads(manifest_path.read_text())
assert all(sha(root/path)==digest for path,digest in manifest.items()),'A source design file changed while packaging'

netlist=ET.parse(hw/'netlist.xml').getroot()
values={c.get('ref'):c.findtext('value') for c in netlist.findall('./components/comp')}
nets={(p.get('ref'),p.get('pin')):net.get('name') for net in netlist.findall('./nets/net') for p in net.findall('node')}
def resistance(value):
    m=re.fullmatch(r'([0-9.]+)([kM]?)',value)
    assert m,value
    return float(m[1])*{'':1,'k':1000,'M':1000000}[m[2]]
rs=[resistance(values[r]) for r in ('R80','R81','R82','R83')];total=sum(rs)
vfull=total/rs[0];vready=total/sum(rs[:2]);vlow=total/sum(rs[:3])
cap=sum(float(re.match(r'([0-9.]+)F',values[c])[1]) for c in ('C1','C2','C3'))
for c in ('C1','C2','C3'):assert nets[(c,'1')]=='VSTORE' and nets[(c,'2')]=='GND'
assert all(nets[('U7',p)]=='GND' for p in ('4','5','6','7','8'))
assert [nets[('K1',p)] for p in ('1','2','3','4','8')]==['MODULE_VBUS','HARV_P','DUT_P','LOAD_P','RELAY_COIL_LOW']
full=.5*cap*vfull*vfull;refill=.5*cap*(vfull*vfull-vlow*vlow);budget=.5*cap*(vready*vready-vlow*vlow)*.9*.8
energy={'basis':'Calculated, not measured. Charge efficiency and cycle energy are assumptions.','capacitance_F':cap,'nominal_threshold_V':{'full':vfull,'ready':vready,'cutoff':vlow},'full_energy_J':full,'cutoff_to_full_energy_J':refill,'conservative_cycle_budget_J':budget,'assumed_loaded_input_W':.7*.03,'assumed_net_charge_efficiency':[.6,.8],'empty_to_full_minutes':[full/(.021*eff)/60 for eff in (.8,.6)],'cutoff_to_full_minutes':[refill/(.021*eff)/60 for eff in (.8,.6)],'assumed_fill_factor_if_Voc_Isc':[.5,.7],'empty_to_full_minutes_if_Voc_Isc':[full/(.021*.7*.8)/60,full/(.021*.5*.6)/60],'assumed_cycle_energy_J':[2,5],'cycles_for_assumed_energy':[math.floor(budget/e) for e in (2,5)],'relay_nominal_coil_W':25/237}
(verification/'energy-estimate.json').write_text(json.dumps(energy,indent=2)+'\n')
summary={'board':'hardware/solar-oracle-walkman-relay.kicad_pcb','pcb_sha256':sha(hw/'solar-oracle-walkman-relay.kicad_pcb'),'kicad_version':drc['kicad_version'],'unrouted':0,'DRC_errors':0,'warnings':dict(collections.Counter(v['type'] for v in drc['violations'])),'schematic_parity_items':0,'ERC_items':0,'ignored_DRC_checks':drc['ignored_checks'],'exclusions':json.loads((hw/'solar-oracle-walkman-relay.kicad_pro').read_text())['board']['design_settings']['drc_exclusions'],'firmware_host_tests':'passed','hardware_function':'NOT_TESTED','firmware_scope':'GPIO and startup layer only; complete measurement application not included','published_source_files_byte_identical':True}
(verification/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
(verification/'design-sha256.json').write_text(json.dumps(manifest,indent=2)+'\n')
# Normalize generated XML metadata only; pin/net definitions remain untouched.
netlist.find('./design/source').text='hardware/solar-oracle-walkman-relay.kicad_sch'
for library in netlist.findall('./libraries/library'):
    uri=library.find('uri')
    if uri is not None and uri.text:
        filename=Path(uri.text).name
        uri.text=('${KIPRJMOD}/' if library.get('logical')=='solar_oracle' else '${KICAD10_SYMBOL_DIR}/')+filename
ET.indent(netlist,space='  ')
ET.ElementTree(netlist).write(hw/'netlist.xml',encoding='utf-8',xml_declaration=True)
print(json.dumps({'verification':summary,'energy':energy,'README_words':len((root/'README.md').read_text().split())},indent=2))
