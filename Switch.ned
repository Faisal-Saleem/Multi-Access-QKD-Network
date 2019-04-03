//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
// @author Faisal Saleem
// @date April 03, 2019
// 

module Switch
{
    // Quatnum Key Distribution switch
    // Uses BB84 protocol to transfer quantum states between clients.
    parameters:
        // Display Paremeters (Color, Grid, Image etc)
        @display("bgb=548,382,#ECFFEC;i=old/switch1;is=n;i2=status/green;bgtt=Quantum Key Distribution Switch;bgg=20,0");
    gates:
        inout fe01;		// FastEthernet 01
        inout fe02;		// FastEthernet 02;
        inout fe03;		// FastEthernet 03;
        inout fe04;		// FastEthernet 04;
        
        inout qu01;		// QuantumInterface 01;
        inout qu02;		// QuantumInterface 02;
        inout qu03;		// QuantumInterface 03;
        inout qu04;		// QuantumInterface 04;
}

