/*
 * AdPlay/UNIX - OPL2 audio player
 * Copyright (C) 2001, 2002 Simon Peter <dn.tlp@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 */

#ifndef H_SERIAL
#define H_SERIAL

#include <ctime>

#include <adplug/opl3duoserial.h>
#include "output.h"

class SerialPlayer: public Player {
private:
    CSerialDuoOpl *opl;
    struct timespec playerTime;

public:
    SerialPlayer(const char *device, int baud);
    virtual ~SerialPlayer();

    void frame() override;

    Copl *get_opl() override;

private:
   static struct timespec diffTime(const struct timespec &t1, struct timespec t2);
};

#endif
