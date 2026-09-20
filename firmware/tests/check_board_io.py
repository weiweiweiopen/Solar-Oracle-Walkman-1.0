"""Host-only startup checks plus independent native XML/header correspondence."""
import json
from pathlib import Path
import re
import subprocess
import sys
import xml.etree.ElementTree as ET

firmware=Path(__file__).resolve().parents[1]
work=Path(sys.argv[1]).resolve() if len(sys.argv)>1 else firmware.parent
header=work/'firmware/include/board_pins.h'
definitions={m[1]:int(m[2]) for m in re.finditer(r'constexpr int (\w+) = (\d+);',header.read_text())}
root=ET.parse(work/'hardware/netlist.xml').getroot()
comp=root.find('./components/comp[@ref="J2"]');ls=comp.find('libsource')
lib=next(l for l in root.findall('./libparts/libpart') if l.get('lib')==ls.get('lib') and l.get('part')==ls.get('part'))
gpio_by_pad={p.get('num'):int(re.search(r'IO(\d+)',p.get('name'))[1]) for p in lib.findall('./pins/pin') if re.search(r'IO(\d+)',p.get('name'))}
expected={net.get('name'):gpio_by_pad[node.get('pin')] for net in root.findall('./nets/net') for node in net.findall('node')
          if node.get('ref')=='J2' and node.get('pin') in gpio_by_pad and not net.get('name').startswith('unconnected-')}
assert definitions==expected,(definitions,expected)
live_header=firmware/'include/board_pins.h'
if "--live" in sys.argv:
    assert live_header.read_bytes()==header.read_bytes(), 'Live firmware header differs from tested candidate'
    live_xml=firmware.parent/'hardware/netlist.xml'
    assert live_xml.read_bytes()==(work/'hardware/netlist.xml').read_bytes(), 'Live netlist differs from checked candidate'
assert len(set(definitions.values()))==len(definitions)
assert not set(definitions.values()) & {0,3,19,20,26,27,28,29,30,31,32,45,46}
output=work/'board_io_host_test'
cmd=['clang++','-std=c++17','-Wall','-Wextra','-Werror','-I'+str(work/'firmware/include'),
     '-I'+str(firmware/'include'),'-I'+str(firmware/'tests/host'),str(firmware/'src/board_io.cpp'),
     str(firmware/'tests/host/board_io_test.cpp'),'-o',str(output)]
subprocess.run(cmd,check=True);subprocess.run([str(output)],check=True)
result={'native_XML_header_match':True,'live_header_and_netlist_match':'--live' in sys.argv,'unique_assigned_GPIOs':len(definitions),'host_startup_tests':'passed',
        'ESP32_cross_compile':'not performed; Arduino-ESP32 toolchain and main application absent'}
(work/'FIRMWARE_VERIFIED.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result,indent=2))
