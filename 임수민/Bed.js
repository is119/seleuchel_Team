var fs = require('./router.js');
const BusinessNetworkConnection = require('composer-client').BusinessNetworkConnection; 
this.bizNetworkConnection = new BusinessNetworkConnection();
const cardname = 'admin@network';
// listnen transaciton events
//emergency Bed Occupied
function listen(){
    this.bizNetworkConnection.on('event',function(event){
        console.log(chalk.bold('Got event!'));
        console.log(event);
    }); //*please compare class 
 

//update bedinfo
 async function updateisOccupy() {
    this.businessNetworkDefinition = await this.bizNetworkConnection.connect(cardname);
     let factory = this.businessNetworkDefinition.getFactory();
     let transaction = factory.newTransaction('org.hackerton','requestEmergencyBed');
     transaction.EmergencyBed = factory.newRelationship('org.hackerton','EmergencyBed','1');
     transaction.EmergencyBed.isOccupied = !isOccupied;
     await this.bizNetworkConnection.submitTransaction(transaction);
 }

 
async function bootstrap() {
        // this.doctorRegistry = await this.bizNetworkConnection.getAssetRegistry('org.hackerton.LandTitle');
        let factory = this.businessNetworkDefinition.getFactory();
        let EmergencyBed = factory.newResource('org.hackerton', 'EmergencyBed', 'PID:1234567890');
        EmergencyBed.BedID = 'StingBedID';
        EmergencyBed.x = 0.0;
        EmergencyBed.y = 0.0;
        EmergencyBed.isOccupied = true;
 
        // Create a new relationship for theBEd
         //Add these to the registry;
        let EmergencyBedRegistry = await this.bizNetworkConnection.getParticipantRegistry('org.hackerton.EmergencyBed');
        await EmergencyBedRegistry.addAll(EmergencyBed);      
}
async function listTitles() { 

        let EmergencyBedRegistry = await this.bizNetworkConnection.getParticipantRegistry('org.hackerton.EmergencyBed');
        //let aResources = await docterRegistry.resolveAll();
        let Resources = await EmergencyBedRegistry.resolveAll();//?
        let table = new Table({
            head: ['BedID', 'x', 'y', 'isOccupied']
        });
        let arrayLength = Resources.length;
        for (let i = 0; i < arrayLength; i++) {
            let tableLine = [];
            tableLine.push(Resources[i].BedID);
            tableLine.push(Resources[i].x);
            tableLine.push(Resources[i].y);
            tableLine.push(Resources[i].isOccupied ? true : false);
            table.push(tableLine);
        };
        return table;
    };
}