
total hours spent: 26 hours.


### July 8, 2025  
**time spent:** 2 hours  

got started with the power stuff today because that felt like a good anchor  
opened up a blank KiCad sheet and just kinda sat there before committing to the first buck converter  
threw in a couple AP62300s, added some random caps that looked about right  
did basic power rails like +3.3VA and +5V, mostly by guessing current draw  
honestly spent more time figuring out resistor values than placing parts  
it's still super rough, but at least the board’s not completely empty anymore  
definitely not thinking about routing yet

| what happened | image |
|---------------|-------|
| got the power rails and buck converters roughly figured out |  <img width="1185" height="930" alt="Screenshot 2025-07-29 221627" src="https://github.com/user-attachments/assets/e2997b11-d2c6-4bb3-9131-2c748177f16b" /> |

---

### July 9, 2025  
**time spent:** 1.5 hours  

dove headfirst into HDMI today and instantly regretted it  
the connector footprint was cursed and I had to double-check every diff pair  
wired up the HDMI chip and some tiny filter caps for signal integrity  
had to decide whether to bother with hotplug detection and i just YOLO’d it in  
tried to keep traces as short as possible even though I haven’t routed anything  
also added pull-ups and random ESD protection that I may or may not actually populate  
got through it alive, but just barely

| what happened | image |
|---------------|-------|
| threw in the hdmi stuff, wasn’t sure if i was wiring it right tbh | <img width="1098" height="515" alt="Screenshot 2025-07-29 221659" src="https://github.com/user-attachments/assets/50efbeda-dd8e-4939-86ec-0cab5e206141" /> |

---

### July 11, 2025  
**time spent:** 2.5 hours  

today was CM4 Lite day, and man this thing has a crazy number of pins  
literally had to scroll through three different PDFs to not mess up the IO mapping  
figured out where to connect PCIe and eMMC signals even though I’m not using either  
started drawing out the main headers and labeling them so I wouldn’t cry later  
threw in level shifters and testpoints just to be safe  

| what happened | image |
|---------------|-------|
| added the cm4 lite footprint and some essentials around it | <img width="946" height="627" alt="Screenshot 2025-07-29 221706" src="https://github.com/user-attachments/assets/d151564b-a407-45e7-ba42-3045035cf730" /> |

---

### July 12, 2025  
**time spent:** 1 hour  

today was about the esp32 and the USB hub, two chips I really like but hate wiring  
added the esp32 footprint and spent too long assigning IOs  
for the usb hub, I was constantly bouncing between the datasheet and KiCad  
wired up USB upstream/downstream lines and crossed my fingers on signal integrity  
threw in some debug headers and left room for ESD stuff I haven’t decided on yet  
also started routing logic enable signals to give me more control later  
kinda messy but functionally complete

| what happened | image |
|---------------|-------|
| hooked up the esp and usb hub chip, still unsure about esd protection here |<img width="1019" height="408" alt="Screenshot 2025-07-29 221714" src="https://github.com/user-attachments/assets/debf89b7-4abb-4e57-93cd-5b7d47f8e346" /> |

---

### July 14, 2025  
**time spent:** 1.5 hours  

this was cleanup day, had to declutter a lot of overlapping nets  
focused on GPIO and voltage domains because things were starting to get scary  
double checked voltage levels everywhere and pulled back any accidental 5V hits  
renamed nets to stuff like USB_D+ and PWR_BTN so I don’t get lost later  
added a few jumpers where I needed config flexibility

| what happened | image |
|---------------|-------|
| the gpio, ethernet, sd signals etc., are getting crowded |<img width="1742" height="708" alt="Screenshot 2025-07-29 221653" src="https://github.com/user-attachments/assets/a439d662-da7e-4999-9111-4ac417e54dc5" />
  |

---

### July 16, 2025  
**time spent:** 2 hours  

felt like expanding the UI side today, so buttons and switches got added  
dropped in an IO expander to control all the random toggles I want  
added RGB LED, backlight control, and the mandatory cyberpunk toggle  
also threw in debug pads and labeled everything just in case I forget stuff later  
double checked how the esp talks to the neopixel

| what happened | image |
|---------------|-------|
| added a bunch of buttons, switches, and gpio expands | <img width="261" height="1035" alt="Screenshot 2025-07-29 221748" src="https://github.com/user-attachments/assets/dfa18253-fcdf-4820-a167-bd55400dc4de" />
 |

---

### July 18, 2025  
**time spent:** 1 hour  

focused entirely on the battery and power switch logic today  
added charging ICs, battery monitor, and some MOSFET magic for switching  
realized I forgot to add thermistor protection, so threw that in last minute  
checked current sense resistor values like 5 times because battery fires aren’t cool  
rewired the main power path so everything’s a bit safer  
design is power-heavy now but kinda elegant  
will probably still debug it with a fire extinguisher nearby

| what happened | image |
|---------------|-------|
| threw in the power switch logic and battery protection circuit |<img width="803" height="701" alt="Screenshot 2025-07-29 221742" src="https://github.com/user-attachments/assets/7514caa4-fe1c-41d6-8a29-2e56360ea030" />
  |

---

### July 20, 2025  
**time spent:** 3 hours  

long session today, mostly organizing the whole schematic properly  
split things into hierarchy sheets because the top level was getting out of control  
reassigned power domains and labeled them to make layout cleaner later  
caught a bunch of dumb mistakes like misnamed nets and flipped diodes  
also started writing notes inside schematic blocks to help future-me  
deleted some sketchy looking wires and redrew for clarity  
design now feels like an actual engineering thing and not a spaghetti nightmare

| what happened | image |
|---------------|-------|
| general cleanup and better power domain separation | <img width="1271" height="683" alt="Screenshot 2025-07-29 221645" src="https://github.com/user-attachments/assets/ea90c333-f921-460d-93c4-ce58ac1d908a" />
  |

---

### July 21, 2025  
**time spent:** 2 hours  

this one was about the screen and making sure it won’t fry  
hooked up the LCD interface and added ESD resistors on all the touch lines  
tried to keep traces short even though I’m still in schematic mode  
double checked the display’s backlight, touchscreen, and data lines  
added a debug header just to probe signals later if things don’t work  
organized the connector pins to make layout easier  
this part was clean.

| what happened | image |
|---------------|-------|
| display interface is finally somewhat sane |<img width="508" height="878" alt="Screenshot 2025-07-29 221758" src="https://github.com/user-attachments/assets/a4210bc6-45a6-406f-8c9e-cc419bbe40d9" />
   |

---

### July 25, 2025  
**time spent:** 1.5 hours  

wrapped up the final round of cleanup and review today  
triple-checked pinouts, footprints, and power rails for errors  
added fiducials, test points, and random extras like boot jumpers  
also finalized the USB-C and HDMI protection stuff  



---
July 26, 2025
**time spent:** 2 hours 

started work on the display PCB today and honestly this one's way calmer than the main board  
got the basic stuff in first power input, the FPC connector for the screen, and some random passives  
had to rotate the layout like 3 times to make the FPC orientation make sense  
added pull-up resistors.

| what happened | image |
|---------------|-------|
| finished the display PCB design, it’s looking clean and minimal | <img width="1171" height="873" alt="Screenshot 2025-07-29 220656" src="https://github.com/user-attachments/assets/63c53e1b-17f5-440c-95d7-4400c1a5e0dc" /> |

---

### July 28, 2025  
**time spent:** 3 hours  

big day finished up the main PCB layout and it’s giving boss battle energy  
revisited every sheet and double checked for footprint mismatches or missing caps  
replaced some jank passives from earlier with proper parts and cleaned up nets  
went full sent on layout had to rip up the power plane.

| what happened | image |
|---------------|-------|
| final layout of the main PCB, all the chaos finally connected | <img width="1511" height="995" alt="Screenshot 2025-07-29 220637" src="https://github.com/user-attachments/assets/6f022bbd-834d-4f86-8158-88ed0497bc34" /> |


---

july 29,2025
**time spent:** 3 hours  

finished doing the firmware, got nothing to say about this one.

