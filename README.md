# Boomba

![Boomba Game Screenshot](screenshot.png "Boomba Game Screenshot")
![Boomba Game Infographic](infographic/infographic.png "Boomba Game Infograpghic")

เกมนี้ชื่อว่า Boomba ได้แรงบันดาลใจมาจากเกม Zuma, Luxor ซึ่งแสดงผลบน Terminal โดยใช้ ncurses สำหรับการแสดงผล และ SDL Mixer สำหรับเสียง

เกมนี้เป็นโปรเจคปลายภาคเรียนที่ 1 ปีที่ 1 วิชา Programming Fundamental

## วิธีติดตั้งและรันตัวเกม (Linux)

Dependencies ของผม :

- `ncurses` 6.2 สำหรับจัดการ Terminal
- `libsdl` และ `libsdl_mixer` 1.2 สำหรับเสียง

คำสั่งติดตั้งบน Arch Linux

``` console
$ sudo pacman -S ncurses sdl_mixer
```

คำสั่งติดตั้งบน Ubuntu

``` console
$ sudo apt-get install libsdl-mixer1.2-dev libncurses5-dev
```

คำสั่งรันตัวเกม

``` console
$ ./main
```

คำสั่งคอมไพล์ (กรณีแก้ไขไฟล์)

``` console
$ make
```

## วิธีติดตั้งและรันตัวเกม (Windows)

เข้าที่เว็บไซต์ Replit

- ลิ้งเข้าเว็บ Replit https://replit.com/@KornYellow/boomba-cli

จากนั้นใน Terminal พิมพ์คำสั่ง

``` console
$ make && ./main
```

## วิธีเล่นเกม

การควบคุมเมนู

- <kbd>↑</kbd> และ <kbd>↓</kbd>: ในการเลือกเมนู
- <kbd>x</kbd>: ยืนยัน / ตกลง
  
การควบคุมตัวผู้เล่น

- <kbd>←</kbd> และ <kbd>→</kbd>: ในการขยับตัวผู้เล่น
- <kbd>x</kbd>: ยิงกระสุน
- <kbd>c</kbd>: สลับสีกระสุน
- <kbd>q</kbd>: หยุดเกม
