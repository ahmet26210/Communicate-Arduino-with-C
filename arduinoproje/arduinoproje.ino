int checknameavailable=0;
char data;
char name[50];
int length=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    if(checknameavailable)
    {
      data=Serial.read();
      if(data!='0')
      {
        name[length]=data;
        length++;
        }
      else
      {
        
           checknameavailable=0;
          implementation();
        }
    
    }
  else{
      data=Serial.read();
      if(data='1')
      checknameavailable=1;
         
    }
    
    }

}

void operation(int data,int control,int n1,int n2)
{
  if(control==0)
  {
    switch(data)
    {
      case 'a': case 'A':
      Serial.println("A");
      break;
      case 'b': case 'B':
      Serial.println("B");
      break;
      case 'c': case 'C':
      Serial.println("C");
      break;
      case 'd': case 'D':
      Serial.println("D");
      break;
      case 'e': case 'E':
      Serial.println("E");
      break;
      case 'f': case 'F':
      Serial.println("F");
      break;
      case 'g': case 'G':
      Serial.println("G");
      break;
      case 'h': case 'H':
      Serial.println("H");
      break;
      case 'i': 
      Serial.println("Büyük i olacak");
      break;
      case 'I':
      Serial.println("I");
      break;
      case 'j': case 'J':
      Serial.println("J");
      break;
      case 'k': case 'K':
      Serial.println("K");
      break;
      case 'l': case 'L':
      Serial.println("L");
      break;
      case 'm': case 'M':
      Serial.println("M");
      break;
      case 'n': case 'N':
      Serial.println("N");
      break;
      case 'o': case 'O':
      Serial.println("O");
      break;
  
      case 'p': case 'P':
      Serial.println("P");
      break;
      case 'r': case 'R':
      Serial.println("R");
      break;
      case 's': case 'S':
      Serial.println("S");
      break;
      case 't': case 'T':
      Serial.println("T");
      break;
      case 'u': case 'U':
      Serial.println("U");
      break;
      case 'v': case 'V':
      Serial.println("V");
      break;
      case 'y': case 'Y':
      Serial.println("Y");
      break;
      case 'z': case 'Z':
      Serial.println("Z");
      break;
      default:
      break;
        
      }
  }
  else
  {
    
      if(n1==-61&&(n2==-89||n2==-121))
      Serial.println("basarili cC");  //Ç
      else if(n1==-60&&(n2==-97||n2==-98))
      Serial.println("basarili yumusak g");//Ğ
      else if(n1==-60&&n2==-79) 
      Serial.println("I buyuk");        //I
      else if(n1==-60&&n2==-80)
      Serial.println("Büyük i olacak");//İ
      else if(n1==-61&&(n2==-74||n2==-106))
      Serial.println("turkce O");         //Ö
      else if(n1==-59&&(n2==-97||n2==-98))
      Serial.println("TUrkce s");       //Ş
      else if(n1==-61&&(n2==-68||n2==-100))
      Serial.println("Turkce u");   //Ü
      
      
    }
      delay(1000);
  }

  void implementation()
  {
    for(int i=0;i<length;i++)
    {
     
           if((int)name[i]>0)
           operation(name[i],0,0,0);
           else
           {
            
           operation('0',1,(int)name[i],(int)name[i+1]);
           name[i]=0;
           i++;
           }
      name[i]=0;
      }

      length=0;
    }
