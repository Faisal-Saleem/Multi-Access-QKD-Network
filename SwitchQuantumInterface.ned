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
simple SwitchQuantumInterface
{
    parameters:
        string macAddress;								//	Quantum MAC Address 
        string exitInterface = "";
        @display("i=block/classifier,red;is=l;bgb=359,329");
    gates:
        inout quantumChannelCommunication;
      	inout subInterface1;
		inout subInterface2;
		inout subInterface3;
		inout subInterface4;
}
