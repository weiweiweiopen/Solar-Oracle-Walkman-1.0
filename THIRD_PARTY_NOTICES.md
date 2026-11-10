# License and attribution

The existing project MIT license and Marc Dusseiller copyright notice are retained in LICENSE. Solar Oracle Walkman's original project contributions, documentation, photographs and generated design material are shared under that repository license except where a third-party notice applies. The license grants no rights to third-party trademarks or implies endorsement by a component manufacturer.

## KiCad assets

Standard symbols, footprints and 3D models originate from the KiCad library community. Redistributed library material retains **CC BY-SA 4.0 with the KiCad library exception**; it is not relicensed as MIT. The exception permits use in electronic designs without imposing the library's share-alike requirement on the resulting design. See [the upstream license and exception](LICENSES/KiCad-library-license.md) and [KiCad 3D model source](https://github.com/KiCad/kicad-packages3D).

This includes standard models bundled under enclosure source archives and the Relay_DPDT_Omron_G6K-2F-Y.step dependency. Embedded STEP metadata is retained. Local module-envelope/detailed reconstruction files are design visualizations, not claims of OEM CAD or dimensional qualification.

## Firmware libraries

Bundled firmware dependencies retain their original license/copyright files. Consult each library's LICENSE/license.txt and source headers; local patches do not remove the original notices. ESP32 Arduino/PlatformIO toolchains are separate dependencies and are not included as prebuilt compiler installations.

## Design lineage and image sources

I–V tester lineage: [IVcurve_tester](https://github.com/weiweiweiopen/IVcurve_tester), originally by Marc Dusseiller. Hardware, enclosure and project presentation work: Shih Wei Chieh / Wise Mouse Culture. Render sources and their design dates are recorded in [image provenance](docs/images/provenance.json). They depict different revisions and are not interchangeable manufacturing references.
