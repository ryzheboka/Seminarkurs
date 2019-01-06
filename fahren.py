programmende = False


def get_sensor_values_raw():
    """
    Gibt eine Liste mit folgendem Inhalt aus: ID des Sensors => Sensorwert
    :return: list sensor_values
    """
    vs = input("Enter the sensor values, seperated by a comma!")    #Eingabe der Sensorwerte, wird später durch die Daten der Sensoren ersetzt
    output = eval("[" + vs + "]")
    return output


def get_sensor_values():
    values = get_sensor_values_raw()
    v = min(values)                 #Es wird nach dem Sensor mit dem geringsten Wert geschaut, da dort dann der naheste Gegenstand/die naheste Wand in Fahrtrichtung liegt.
    return values.index(v), v      #get_sernsor_values besteht jetzt aus der Nummer/ID des Sensors (Beginn ist die 0) und dem Wert des Sensors.


def run():
    sensor, distance = get_sensor_values()  #Aufteilung des ID und des Wertes in 2 Vairablen, da beide unabhängig voneinander benötigt werden.
    print("SensorId #", sensor)
    print(distance)
    while (distance > 10):                  #Solange der geringste Abstand zu einem Gegenstand/einer Wand mehr als x cm, als Beispiel 10 beträgt, soll der Roboter weiterhin geradeaus fahren.
        motorenlinks = 1                    #Dafür werden sowohl der linke als auch der rechte Motorblock aktiviert, genauere Ausarbeitung dieses Befehls wird ausgearbeitet, wenn ich weiß, wie der Roboter genau fährt und wie ich die benutzten Motoren ansteuern kann.
        motorenrechts = 1
        print("Roboter fährt vorwärts, da kein Sensor einen Abstand von weniger als x (10) cm zu dem nächsten Gegenstand/der nächsten Wand hat!")
        distance = get_sensor_values()[1]   #Die Sensorwert werden die ganze Zeit hindurch gemesssen und der jeweils geringste Wert wird verarbeitet.
        if(programmende):
            break
        exit(42)
    else:
        motorenlinks = 0                    #Sollte einer der Sensoren vorne am Roboter einen Gegenstand näher als x (10) cm erkennen, stoppt der Roboter.
        motorenrechts = 0
        print("Roboter bleibt stehen, da ein Gegenstand innerhalb von x (10) cm vor dem Roboter liegt.")
        bilderkennung = int(input("Enter a '0'(zero), if the camera spots a wall, enter a '1', if the camera spots a cube or enter a '2', if the camera spots a ball!"))   #Diese Eingabe simuliert die Auswertung der Kamera. Muss die Kamera zur Auswertung später wissen, wo vor dem Roboter der Gegenstand/die Wand, die zu erkennen ist, ist, würe dies machbar, aber momentan ist es sinnlos, da ich davon ausgehe, dass die Kamera diese Information nicht unebdingt benötigt.
        if bilderkennung == 0:
            print("Wand erkannt")   #Roboter muss sich drehen           ---> !!!!!NOCH PROGRAMMIEREN!!!!!
        elif bilderkennung == 1:
            print("Würfel erkannt") #Roboter muss den Würfel aufheben   ---> !!!!!NOCH PROGRAMMIEREN!!!!!
        elif bilderkennung == 2:
            print("Kugel erkannt")  #Roboter muss die Kugel aufheben    ---> !!!!!NOCH PROGRAMMIEREN!!!!!
        else:
            print("ERROR!!!")
        run()
run()