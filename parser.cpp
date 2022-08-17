#include "parser.h"

String item;
String trama = "";

String getFromTerminal()
{
  trama = "";
  trama =  Serial.readString(); //leo todo
  StringSplitter *split = new StringSplitter(trama, 's', 35); // separo para que lea hasta la fase S
  trama = split->getItemAtIndex(0); //guardo lo que separé hasta la "s"
  trama.remove(trama.length() - 2); //al final del string da cada fase guarda dos \t => se sacan

  //empiezo a separar por items
  StringSplitter *splitter = new StringSplitter(trama, '\t', 35); // new StringSplitter(string_to_split, delimiter, limit) Max 5 strings
  int itemCount = splitter->getItemCount();                      // Obtengo la cantidad de subStrings del mensaje entrante separados por un ";".

  //reinicio el string largo de datos
  trama = "";
  for (int i = 0; i < itemCount; i++)
  {
    item = splitter->getItemAtIndex(i); // Obtengo el String ya separado del buffer.

    if (item != "") // si parseo un string vacio
    {
      item = item + ',';
      trama = trama + item;
    }
    
  }
  Serial.flush();
  return (trama);
}
