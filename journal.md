total hours spent: 43 hours.


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
| added a bunch of buttons, switches, and gpio expands | <img width="261" height="1035" alt="Screenshot 2025-07-29 221748" src="https://github.com/user-attachments/assets/dfa18253-fcdf-4820-a167-bd55400dc4de" /> |

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

### July 22, 2025  
**time spent:** 1.5 hours  

wrapped up the final round of cleanup and review today  
triple-checked pinouts, footprints, and power rails for errors  
added fiducials, test points, and random extras like boot jumpers  
also finalized the USB-C and HDMI protection stuff  

---

### July 23, 2025
**time spent:** 4 hours  

worked on deciding the dimensions for the pcb borders and made sure that it fit my case dimensions that i have planned, also many components i placed on the board, just the process of deciding the border length took a lot of time, started routing the pcb and i finished abtu 20% of it, i am thinking of importing it to easy eda pro and autorouting it but i want the source files so ill keep it

---

### july 24,2025 
**time spent:** 3 hours  

today i finished routing the display pcb, and started routing the main pcb, it did take a lot of retries since i had to replace parts and i finally found a suitable arrangement, routig all the parts in the main pcb was pretty hectic, ive finished like 70% of it, i've got school stuff to do now so imma take the night off

---

### July 26, 2025
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

### july 29,2025
**time spent:** 3 hours  

finished doing the firmware, got nothing to say about this one.

---

### July 29, 2025 ( in the night ) 
**time spent:** 2 hours  
Did more work on the case for the display PCB today. Most of the time went into figuring out the outer dimensions so the board actually fits in clean. Kept adjusting a few mm here and there to match the rough size I had in my head. Took way longer than it should’ve. Once that was sorted, I started adding the cutouts and screw holes. made sure the ports had breathing room, and triple-checked all the hole spacing. Don’t wanna be that guy who forgets to leave space for the USB port. Didn’t bother adding fillets or rounded corners yet just getting the basic shape right for now. Might tweak the aesthetics later once I test fit the first cut. But yeah, it’s finally starting to look like a proper case.
| what happened | image |
|---------------|-------|
| sneak peaks | <img width="1242" height="858" alt="Screenshot 2025-08-02 202147" src="https://github.com/user-attachments/assets/c70c1673-6f8d-4a39-b6ea-db23ebccc63b" /> |
| sneak peaks | <img width="690" height="763" alt="Screenshot 2025-08-02 202235" src="https://github.com/user-attachments/assets/44667d6b-108f-41e5-8cb7-69a62158e1c7" /> |

---

### July 30, 2025( early morning )
**time spent** 4 hours
Started designing the bottom half of the display case today. The goal was to keep it simple but still make sure everything lines up clean. Took a bit of time messing with dimensions—mainly double checking hole positions it matched the PCB layout. Rounded off the corners to make it less boxy and added a small notch for cable clearance later if I need it. The cutouts for the screen area and the mounts came out nice in the 3D preview.

Honestly just getting the case to sit right with the PCB was half the battle, but it looks solid now. Ready to move on to the top half next.
| what happened | image |
|---------------|-------|
| sneak peaks | <img width="1217" height="815" alt="Screenshot 2025-08-02 201317" src="https://github.com/user-attachments/assets/4225d18f-129e-40b3-a4fd-c140105f2112" /> |
| sneak peaks | <img width="1644" height="974" alt="Screenshot 2025-08-02 201557" src="https://github.com/user-attachments/assets/e2a8842c-8c96-45ba-b070-0578f33e4b76" /> |

---

### July 30, 2025( night)
**time spent** 2 hours

I started working on the top half of the case. This part was kind of annoying, to be honest. I had to figure out the exact cutout for the display and ensure it sat flush without pressing too hard on the screen. It took a few tries to get the depth right. I kept toggling between the model and the actual display dimensions just to be sure.Then came the USB port clearance, which was a real hassle. Tiny shifts made it either not fit or too loose. I finally added a small beveled area around it so it wouldn’t scrape while plugging things in. I also had to make sure the mounting holes lined up perfectly with the bottom half. I used offsets and several measuring tools in Fusion to get it right. I added a little lip around the edges to help with alignment when snapping it on, and I created some space inside for routing wires from the display. It’s not the prettiest lid, but it gets the job done. I might refine the outer surface later to make it look cleaner. For now, I’m just focused on function.
| what happened | image |
|---------------|-------|
| sneak peaks | <img width="1215" height="748" alt="Screenshot 2025-08-02 194902" src="https://github.com/user-attachments/assets/ae899ca2-b7e2-438b-9bfd-3f738996ee80" /> |
| sneak peaks | <img width="1080" height="617" alt="Screenshot 2025-08-02 194959" src="https://github.com/user-attachments/assets/679d8518-cd1c-401e-95ed-dd554ddf62cc" /> |

---

### July 31,2025
**time spent** 2 hours

spent most of the evening just modeling the top half of the display case. it honestly took longer than expected lining everything up with the pcb was kind of a pain. had to double check the display cutout, standoff placement, and make sure nothing would crash into the components later. i played around with the screen window quite a bit… didn’t want it to look bulky, but also didn’t want it too snug and risk it scraping the screen when assembled. added a few guiding walls inside so the pcb can sort of “slot in” when it’s time. should help with alignment too. tweaked tolerances here and there, especially around the screen opening. might still need adjustments after the first print, but visually it’s looking nice.
not the most fun part of the build, but we’re getting there.

| what happened | image |
|---------------|-------|
| sneak peaks | <img width="1214" height="804" alt="Screenshot 2025-08-02 201930" src="https://github.com/user-attachments/assets/85abaf62-bda3-4362-9c8d-1092e5943701" />
 |
| sneak peaks | <img width="1485" height="1089" alt="Screenshot 2025-08-02 202037" src="https://github.com/user-attachments/assets/a56f7d25-29db-4b58-b25d-3bcca4fabee7" />  |

---
