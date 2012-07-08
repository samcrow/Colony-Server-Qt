#include "csvloader.hpp"

CSVLoader::CSVLoader(QObject *parent) :
    QObject(parent)
{

}

QList<Colony *> CSVLoader::readFile(QWidget * parent){
    QFile csv(this);

    QSettings settings;
    //Get the CSV path from the settings
    QString csvPath = settings.value("data/path", "").toString();

    if(csvPath.isEmpty()){
        csvPath = QFileDialog::getOpenFileName(parent, "Choose a CSV file with colony data", "", "CSV files (*.csv)");
        if(!csvPath.isEmpty()){
            settings.setValue("data/path", csvPath);
        } else {
            exit(0);//If the user clicked the cancel button, quit the application
        }
    } else {
        //If the path from the preferences wasn't emtpy, try opening it
        csv.setFileName(csvPath);
        csv.open(QFile::ReadOnly | QFile::Text);
        if(!csv.isOpen()){
            //Path from settings wasn't valid. Choose the file again.
            csvPath = QFileDialog::getOpenFileName(parent, "Choose a CSV file with colony data", "", "CSV files (*.csv)");
            if(!csvPath.isEmpty()){
                settings.setValue("data/path", csvPath);
            } else {
                exit(0);//If the user clicked the cancel button, quit the application
            }
        }
    }

    csv.setFileName(csvPath);
    //File opening options
    csv.open(QFile::ReadOnly | QFile::Text);
    if(!csv.isOpen()){
        qCritical() << "Could not open colony file!";
    }

    QTextStream stream(&csv);//Create a stream thing for the file

    QList<Colony *> colonies;

    stream.readLine();//Read the first line of the file, containing the headers. This keeps it from getting read in the loop later.

    while(true){
        QString line = stream.readLine();
        if(line == NULL) break;//Get out of the loop if there are no more lines to read



        //Each line is in the form <colonyNumber>,<XCoord>,<YCoord>,(some other things)
        QStringList parts = line.split(",", QString::SkipEmptyParts);

        if(parts.size() >= 4){//If the string was successfully split into three parts

            //OK-ness states for parsing the number strings into ints
            bool colonyNumberOK;
            bool xOK;
            bool yOK;

            int colonyNumber = parts.at(0).toInt(&colonyNumberOK);
            int x = parts.at(1).toInt(&xOK);
            int y = parts.at(2).toInt(&yOK);

            bool isActive = parts.at(3).startsWith('A');

            if(xOK && yOK && colonyNumberOK){
                //Create a new colony thing
                Colony *newColony = new Colony(colonyNumber, x, y, isActive);
                colonies.append(newColony);
            } else {
                qWarning() << "The following line contains non-integer characters:\n" << line;
            }

        }else{//If the string was not successfully split into parts
            qWarning() << "The following line could not be parsed:\n" << line;
        }
    }


    csv.close();//Close the file
    return colonies;
}

