
/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */


// safety againts double-include
#ifndef pca9535bounce_h
#define pca9535bounce_h
#include <Arduino.h>
#include <Bounce.h>

class pca9535bounce : public Bounce
{
    public:
        Bounce(uint8_t pin, unsigned long interval_millis ); 
        void init(pca9535 *expander, uint8_t pin, unsigned long interval_millis );
        pca9535* device;
};

#endif
// *********** END OF CODE **********
