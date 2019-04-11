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
network Network
{
    parameters:
        @display("bgb=402,278,#FFE4CA;i=block/network;i2=status/connect;bgl=2");
    submodules:
        switch: Switch {
            @display("p=203,133");
        }
        client01: Client {
            @display("p=42,41");
            name = "Cliant 01";
            macAddress = "AA:AA:AA:AA:AA:01";
        }
        client02: Client {
            @display("p=44,206");
            name = "Cliant 02";
            macAddress = "AA:AA:AA:AA:AA:02";
        }
        client03: Client {
            @display("p=339,42");
            name = "Cliant 03";
            macAddress = "AA:AA:AA:AA:AA:03";
        }
        client04: Client {
            @display("p=344,213");
            name = "Cliant 04";
            macAddress = "AA:AA:AA:AA:AA:04";
        }
    connections:
        client01.publicInterface <--> switch.fe01;
        client02.publicInterface <--> switch.fe02;
        client03.publicInterface <--> switch.fe03;
        client04.publicInterface <--> switch.fe04;
        client01.quantumInterface <--> switch.qu01;
        client02.quantumInterface <--> switch.qu02;
        client03.quantumInterface <--> switch.qu03;
        client04.quantumInterface <--> switch.qu04;
}
