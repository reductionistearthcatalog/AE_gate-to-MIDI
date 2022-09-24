# AE_gate-to-MIDI
Code and description of a DIY AE module based on an arduino nano that converts trigger/gates in AE Modular to USB-MIDI note-on signals

# Disclaimer
This is experimental hardware and software. I can make no guarantees of it's function.

# Hardware
The hardware side is composed of an Arduino nano which is powered by 5V and ground from the AE Modular power ribbon. Arduino digital pins D2 to D9 are connected to pin header inputs, where gates or triggers from AE Modular can be patched in. Digital pins D2 to D9 are also connected to ground via 100k resistors (as shown in  <a href="https://github.com/TuesdayNightMachines/AEModular/blob/master/Generative_CV_Sequencer/TTNM_AEModular_GenerativeCVseq_Circuit.jpg">this schematic</a> from the Tuesday Night Machines). The Arduino also connects via USB to the USB MIDI host 

NOTE: it is possible that if the USB is connected and the AE Modular system is powered off, the USB host is back-powering the Arduino and, by extension, the AE Modular. I do not know enough about electronics to resolve this, or how big of a safety issue it is.

# Software
The USB host that the Arduino is connected to needs to run the <a href="https://projectgus.github.io/hairless-midiserial/?source=post_page---------------------------">Hairless MIDI-serial bridge</a> or <a href="https://github.com/cjbarnes18/ttymidi">ttymidi</a>. The baud rate is set to 115200, but this can be changed in the Arduino code.

# Usage
Once a MIDI connection is established, and trigger/gate signals are patched into the pin header on the DIY module, MIDI note-ons are sent from the Arduino on channel 1. If a gate is sent to the bottom input, a MIDI note 1 note-on is sent. If a gate is sent to the second input from bottom, a MIDI note 2 note-on is sent, and so on.

If multiple Arduino nano-based devices are connected via USB to the same host, it can be difficult to tell which device device number corresponds to which physical device. The Arduino code also contains a control change responder, such that if a CC number 3 control change signal is received, the Arduino responds with a CC number 127 value of 1 on channel 1.
