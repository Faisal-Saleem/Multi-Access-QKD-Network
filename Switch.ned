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
        @display("bgb=441,711,#ECFFEC;i=abstract/switch;is=n;i2=status/green;bgtt=Quantum Key Distribution Switch");
    gates:
        inout fe01;		// FastEthernet 01
        inout fe02;		// FastEthernet 02;
        inout fe03;		// FastEthernet 03;
        inout fe04;		// FastEthernet 04;
        inout qu01;		// QuantumInterface 01;
        inout qu02;		// QuantumInterface 02;
        inout qu03;		// QuantumInterface 03;
        inout qu04;		// QuantumInterface 04;
    submodules:
        processor: Processor {
            //	Processor
            @display("p=71,342;is=l");
        }
        f01: SwitchPublicInterface {
            //	FastEthernet01 Interface
            @display("p=51,657;is=n");
        }
        f02: SwitchPublicInterface {
            @display("p=169,657;is=n");
        }
        f03: SwitchPublicInterface {
            @display("p=278,657;is=n");
        }
        f04: SwitchPublicInterface {
            @display("p=388,657;is=n");
        }
        q01: SwitchQuantumInterface {
            @display("p=43,93;is=n");
        }
        q02: SwitchQuantumInterface {
            @display("p=122,42;is=n");
        }
        q03: SwitchQuantumInterface {
            @display("p=297,40;is=n");
        }
        q04: SwitchQuantumInterface {
            @display("p=400,93;is=n");
        }
        processingQueue: ProcessingQueue {
            @display("p=210,501");
        }
        quantumStatesProcessor: QuantumStatesQueue {
            @display("p=217,137");
        }
        switchMemory: SwitchMemory {
            @display("p=332,340");
        }
    connections:
        fe01 <--> f01.publicChannelCommunication;
        fe02 <--> f02.publicChannelCommunication;
        fe03 <--> f03.publicChannelCommunication;
        fe04 <--> f04.publicChannelCommunication;
        qu01 <--> q01.quantumChannelCommunication;
        qu02 <--> q02.quantumChannelCommunication;
        qu03 <--> q03.quantumChannelCommunication;
        qu04 <--> q04.quantumChannelCommunication;
        processor.memoryBus <--> switchMemory.processorBus;
        processor.quantumInterfaceCommunication <--> quantumStatesProcessor.inFromProcessor;
        processingQueue.processorCommunication <--> processor.publicInterfaceCommunication;
        f01.processorCommuniation <--> processingQueue.f01;
        f02.processorCommuniation <--> processingQueue.f02;
        f03.processorCommuniation <--> processingQueue.f03;
        f04.processorCommuniation <--> processingQueue.f04;
        q01.subInterface1 <--> quantumStatesProcessor.interface01;
        q02.subInterface2 <--> quantumStatesProcessor.interface02;
        q03.subInterface3 <--> quantumStatesProcessor.interface03;
        q04.subInterface4 <--> quantumStatesProcessor.interface04;
        q01.subInterface2 <--> q02.subInterface1;
        q02.subInterface3 <--> q03.subInterface2;
        q03.subInterface4 <--> q04.subInterface3;
        q01.subInterface4 <--> q04.subInterface1;
        q02.subInterface4 <--> q04.subInterface2;
        q03.subInterface1 <--> q01.subInterface3;
}
