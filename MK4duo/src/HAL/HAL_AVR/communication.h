/**
 * MK & MK4due 3D Printer Firmware
 *
 * Based on Marlin, Sprinter and grbl
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 * Copyright (C) 2013 - 2016 Alberto Cotronei @MagoKimbra
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define START           "start"               // start for host
#define OK              "ok"                  // ok answer for host
#define OKSPACE         "ok "                 // ok plus space 
#define ER              "Error:"              // error for host
#define WT              "wait"                // wait for host
#define ECHO            "Echo:"               // message for user
#define CFG             "Config:"             // config for host
#define CAP             "Cap:"                // capabilities for host
#define INFO            "Info:"               // info for host
#define BUSY            "busy:"               // buys for host
#define RESEND          "Resend:"             // resend for host
#define WARNING         "Warning:"            // warning for host
#define TNAN            "NAN"                 // NAN for host
#define TINF            "INF"                 // INF for host
#define PAUSE           "//action:pause"      // command for host that support action
#define RESUME          "//action:resume"     // command for host that support action
#define DISCONNECT      "//action:disconnect" // command for host that support action

#define SERIAL_INIT(baud)                   do{ MKSERIAL.begin(baud); HAL::delayMilliseconds(1); }while(0)
#define SERIAL_WRITE(v)                     (MKSERIAL.write(v))
#define SERIAL_PRINT(v)                     (MKSERIAL.print(v))
#define SERIAL_PRINT_F(v,n)                 (MKSERIAL.print(v,n))

// Things to write to serial from Program memory. Saves 400 to 2k of RAM.
FORCE_INLINE void serialprintPGM(const char* str) {
  while (char ch = pgm_read_byte(str++)) MKSERIAL.write(ch);
}

#define SERIAL_PS(message)                  (serialprintPGM(message))
#define SERIAL_PGM(message)                 (serialprintPGM(PSTR(message)))

#define SERIAL_S(srt)                       SERIAL_PGM(srt)
#define SERIAL_M(msg)                       SERIAL_PGM(msg)
#define SERIAL_T(txt)                       (serial_print(txt))
#define SERIAL_V(val, ...)                  (serial_print(val, ## __VA_ARGS__))
#define SERIAL_C(c)                         SERIAL_WRITE(c)
#define SERIAL_E                            SERIAL_WRITE('\n')

#define SERIAL_MT(msg, txt)                 (serial_print_pair(PSTR(msg), txt))
#define SERIAL_MV(msg, val, ...)            (serial_print_pair(PSTR(msg), val, ## __VA_ARGS__))

#define SERIAL_SM(srt, msg)                 do{ SERIAL_S(srt); SERIAL_M(msg); }while(0)
#define SERIAL_ST(srt, txt)                 do{ SERIAL_S(srt); SERIAL_T(txt); }while(0)
#define SERIAL_SV(srt, val, ...)            do{ SERIAL_S(srt); SERIAL_V(val, ## __VA_ARGS__); }while(0)
#define SERIAL_SMT(srt, msg, txt)           do{ SERIAL_S(srt); SERIAL_MT(msg, txt); }while(0)
#define SERIAL_SMV(srt, msg, val, ...)      do{ SERIAL_S(srt); SERIAL_MV(msg, val, ## __VA_ARGS__); }while(0)

#define SERIAL_EM(msg)                      (serialprintPGM(PSTR(msg "\n")))
#define SERIAL_ET(txt)                      do{ SERIAL_T(txt); SERIAL_E; }while(0)
#define SERIAL_EV(val, ...)                 do{ SERIAL_V(val, ## __VA_ARGS__); SERIAL_E; }while(0)
#define SERIAL_EMT(msg, txt)                do{ SERIAL_MT(msg, txt); SERIAL_E; }while(0)
#define SERIAL_EMV(msg, val, ...)           do{ SERIAL_MV(msg, val, ## __VA_ARGS__); SERIAL_E; }while(0)

#define SERIAL_L(srt)                       do{ SERIAL_S(srt); SERIAL_E; }while(0)
#define SERIAL_LM(srt, msg)                 do{ SERIAL_S(srt); SERIAL_EM(msg); }while(0)
#define SERIAL_LT(srt, txt)                 do{ SERIAL_S(srt); SERIAL_T(txt); SERIAL_E; }while(0)
#define SERIAL_LV(srt, val, ...)            do{ SERIAL_S(srt); SERIAL_V(val, ## __VA_ARGS__); SERIAL_E; }while(0)
#define SERIAL_LMT(srt, msg, txt)           do{ SERIAL_S(srt); SERIAL_MT(msg, txt); SERIAL_E; }while(0)
#define SERIAL_LMV(srt, msg, val, ...)      do{ SERIAL_S(srt); SERIAL_MV(msg, val, ## __VA_ARGS__); SERIAL_E; }while(0)

FORCE_INLINE void serial_print(const char *v)   { MKSERIAL.print(v); }
FORCE_INLINE void serial_print(char v)          { MKSERIAL.print(v); }
FORCE_INLINE void serial_print(int v)           { MKSERIAL.print(v); }
FORCE_INLINE void serial_print(long v)          { MKSERIAL.print(v); }
FORCE_INLINE void serial_print(double v)        { MKSERIAL.print(v); }
FORCE_INLINE void serial_print(float v, int n)  { MKSERIAL.print(v, n); }
FORCE_INLINE void serial_print(uint8_t v)       { MKSERIAL.print((int)v); }
FORCE_INLINE void serial_print(uint16_t v)      { MKSERIAL.print((int)v); }
FORCE_INLINE void serial_print(uint32_t v)      { MKSERIAL.print((long)v); }
FORCE_INLINE void serial_print(bool v)          { MKSERIAL.print((int)v); }
FORCE_INLINE void serial_print(void *v)         { MKSERIAL.print((int)v); }

FORCE_INLINE void serial_print_pair(const char* msg, const char *v)   { serialprintPGM(msg); MKSERIAL.print(v); }
FORCE_INLINE void serial_print_pair(const char* msg, char v)          { serialprintPGM(msg); MKSERIAL.print(v); }
FORCE_INLINE void serial_print_pair(const char* msg, int v)           { serialprintPGM(msg); MKSERIAL.print(v); }
FORCE_INLINE void serial_print_pair(const char* msg, long v)          { serialprintPGM(msg); MKSERIAL.print(v); }
FORCE_INLINE void serial_print_pair(const char* msg, float v, int n)  { serialprintPGM(msg); MKSERIAL.print(v, n); }
FORCE_INLINE void serial_print_pair(const char* msg, double v)        { serialprintPGM(msg); MKSERIAL.print(v); }
FORCE_INLINE void serial_print_pair(const char* msg, uint8_t v)       { serial_print_pair(msg, (int)v); }
FORCE_INLINE void serial_print_pair(const char* msg, uint16_t v)      { serial_print_pair(msg, (int)v); }
FORCE_INLINE void serial_print_pair(const char* msg, uint32_t v)      { serial_print_pair(msg, (long)v); }
FORCE_INLINE void serial_print_pair(const char* msg, bool v)          { serial_print_pair(msg, (int)v); }
FORCE_INLINE void serial_print_pair(const char* msg, void *v)         { serial_print_pair(msg, (int)v); }

#endif
