// /*
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License version 2 as published by the Free Software Foundation.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
// 
// You should have received a copy of the GNU Library General Public License
// along with this library; see the file COPYING.LIB.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.*/
// 
// #include "utils.h"
// 
// namespace fl{
// 	namespace utils{
// 
// 		inline int GetExpoBase2(double d)
// 		{
// 			int i = 0;
// 			((short *)(&i))[0] = (((short *)(&d))[3] & (short)32752); // _123456789ab____ & 0111111111110000
// 			return (i >> 4) - 1023;
// 		}
// 		bool equals(double d1, double d2)
// 		{
// 			if (d1 == d2)
// 				return true;
// 			int e1 = GetExpoBase2(d1);
// 			int e2 = GetExpoBase2(d2);
// 			int e3 = GetExpoBase2(d1 - d2);
// 			if ((e3 - e2 < -48) && (e3 - e1 < -48))
// 				return true;
// 			return false;
// 		}
// 	}
// }
// 
