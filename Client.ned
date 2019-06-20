
module Client
{
    parameters:
        @display("bgb=541,543,#ECFFEC;i=block/telnet;is=n;i2=status/green;bgtt=Quantum Key Distribution Switch");
        string hostname;
    gates:
        inout publicInterface;
        inout quantumInterface;

    submodules:
        clientPublicInterface: ClientPublicInterface {
            @display("p=462,474");
        }
        clientQuantumInterface: ClientQuantumInterface {
            @display("p=474,201");
        }
        DL: ClientFilterDL {
            @display("p=225,52;t=\\");
        }
        DR: ClientFilterDR {
            @display("p=332,52;t=/");
        }
        H: ClientFilterH {
            @display("p=225,162;t=--");
        }
        V: ClientFilterV {
            @display("p=332,240;t=|");
        }
        quantumStatesGenerator: QuantumStatesGenerator {
            @display("p=64,201");
        }
        clientProcessor: ClientProcessor {
            @display("p=64,475");
        }
        clientFilterDiagonal: ClientFilterDiagonal {
            @display("p=225,356;t=x");
        }
        clientFilterStraight: ClientFilterStraight {
            @display("p=332,356;t=+");
        }
        clientMemory: ClientMemory {
            @display("p=123,379");
        }
    connections:
        clientPublicInterface.externalCommunication <--> {  delay = 100ms; } <--> publicInterface;
        clientQuantumInterface.quantumChannelCommunication <--> {  delay = 100ms; } <--> quantumInterface;
        DL.polarizedLight --> {  delay = 100ms; } --> clientQuantumInterface.dl;
        DR.polarizedLight --> {  delay = 100ms; } --> clientQuantumInterface.dr;
        H.polarizedLight --> {  delay = 100ms; } --> clientQuantumInterface.h;
        V.polarizedLight --> {  delay = 100ms; } --> clientQuantumInterface.v;
        clientProcessor.publicInterfaceCommunication <--> {  delay = 100ms; } <--> clientPublicInterface.processorCommunication;
        quantumStatesGenerator.DL --> {  delay = 100ms; } --> DL.unpolarizedLight;
        quantumStatesGenerator.DR --> {  delay = 100ms; } --> DR.unpolarizedLight;
        quantumStatesGenerator.H --> {  delay = 100ms; } --> H.unpolarizedLight;
        quantumStatesGenerator.V --> {  delay = 100ms; } --> V.unpolarizedLight;
        clientProcessor.quantumInterfaceCommunication <--> {  delay = 100ms; } <--> quantumStatesGenerator.processorCommunication;
        clientQuantumInterface.diagonal --> {  delay = 100ms; } --> clientFilterDiagonal.polarizedLightIn;
        clientQuantumInterface.flat --> {  delay = 100ms; } --> clientFilterStraight.polarizedLightIn;
        clientFilterDiagonal.polarizedLightOut --> {  delay = 100ms; } --> quantumStatesGenerator.Diagonal;
        clientFilterStraight.polarizedLightOut --> {  delay = 100ms; } --> quantumStatesGenerator.Straight;
}

