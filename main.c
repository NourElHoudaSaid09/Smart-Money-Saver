//kujjehmode = 1 => password entry mode for opening it
//kujjehmode = 2 => password change mode

//kujjeh content is located between eeprom0 and eeprom9
//kujjeh password is located between eeprom10 and eeprom40
#define solenoid rd4_bit
#define buzzer rd5_bit
#define solenoiddir trisd4_bit
#define buzzerdir trisd5_bit


float counter;
long i;
long oldstate = 0;
long part4 = 0;
long part3 = 0;
long part2 = 0;
long part1 = 0;

char scratchstring[16];
char clearstring[] = "                ";

char internalpasswordarray[20];
char externalpasswordarray[20];

char oldkp = 0;
char oldkp2 = 0;

char message [12]={0,0,0,0,0,0,0,0,0,0,0,0};
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;

sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;


sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;

// Keypad module connections
char  keypadPort at PORTB;
// End Keypad module connections

int kujjehmode = 0;
int previouskujjehmode = 0;

int passwordpointer = 0;

int withdrawalpointer = 0;
char withdrawalstring[16];
long withdrawalvalue = 0;

void checkkeypad(void);
long checkinputquantity(void);
char keypadkeycheck(void);

void storeineeprom(void)
{
 part4 = (oldstate >> 24)&0b11111111;
 part3 = (oldstate >> 16) & 0b11111111;
 part2 = (oldstate >> 8) & 0b11111111;
 part1 = (oldstate & 0b11111111);
 eeprom_write(0,part1);
 delay_ms(10);
 eeprom_write(1,part2);
 delay_ms(10);
 eeprom_write(2,part3);
 delay_ms(10);
 eeprom_write(3,part4);
 delay_ms(10);
}

void loadfromeeprom(void)
 {
   part1= EEPROM_Read(0);
    part2 = EEPROM_Read(1);
    part3 = EEPROM_Read(2);
    part4 = eeprom_read(3);

    oldstate = (part4 << 24);
    oldstate= oldstate + (part3 << 16);
    oldstate = oldstate + (part2 << 8);
    oldstate = oldstate + part1;
 }
 
int keypadinput = - 5;

int scratch = 0;
 
void main() {

solenoid = 0;
buzzer = 0;
solenoiddir = 0;
buzzerdir = 0;

  part4 = ((oldstate >> 24) & 0b11111111);
  part3 = ((oldstate >> 16)& 0b11111111);
  part2 = ((oldstate >> 8)&0b11111111);
  part1 = (oldstate & 0b11111111);

  Keypad_Init();                           // Initialize Keypad

 Lcd_Init();                        // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR);
                 // Clear display
  lcd_cmd(_LCD_RETURN_HOME);
  Lcd_Cmd(_LCD_CURSOR_OFF);
   LongToStr(oldstate,message);

    loadfromeeprom();

  while(1)
  {
       if(RD0_bit == 1)
   {   i=250;


    loadfromeeprom();
    oldstate = oldstate +i;
      storeineeprom();
       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       Lcd_Out(1, 1, "Welcome Back!");
       lcd_out(2,1,clearstring);
        Lcd_Out(2, 1, "You added 250");
        /*lcd_out(3 ,1 , "You have now:");
        longtostr(oldstate,scratchstring);
        lcd_out(4,1 , scratchstring);*/
        delay_ms(2000);
        lcd_cmd(_LCD_CLEAR);
    }
    else if (RD1_bit == 1)
    {   i=500;

    loadfromeeprom();
    oldstate = oldstate +i;
    storeineeprom();
         lcd_cmd(_LCD_CLEAR);
         lcd_cmd(_LCD_RETURN_HOME);
         Lcd_Out(1, 1, "Welcome Back!");
         lcd_out(2,1,clearstring);
         Lcd_Out(2, 1, "You added 500");
         /*lcd_out(3 , 1 , "You have now:");
         longtostr(oldstate,scratchstring);
         lcd_out(4,1 , scratchstring);*/
         delay_ms(2000);
         lcd_cmd(_LCD_CLEAR);
    }
    
    else if(RD2_bit== 1)
    {


         
         lcd_cmd(_LCD_CLEAR);
         lcd_cmd(_LCD_RETURN_HOME);
         lcd_out(4,1 , scratchstring);
         Lcd_Out(1, 1, "Welcome Back!");
         lcd_out(2, 1, clearstring);
         Lcd_Out(2, 1, "Money Entered:");

         lcd_out(4,1 , clearstring);
         i = checkinputquantity();
         
         loadfromeeprom();
         oldstate = oldstate +i;
         storeineeprom();

         lcd_cmd(_LCD_CLEAR);
         lcd_cmd(_LCD_RETURN_HOME);
         Lcd_Out(1, 1, "Thank You!!!");

         /*lcd_out(3 ,1 , "You have now:");
         longtostr(oldstate,scratchstring);
         lcd_out(4,1,clearstring);
         lcd_out(4 ,1 , scratchstring);*/
         
         delay_ms(2000);
     }
     
    checkkeypad();
  }
}

void checkkeypad(void)
{
   int kp = 0;
   kp = Keypad_Key_press();
   if (kp == 0)
      {
      oldkp = 0;
      return;
      };
      
 switch (kp) {
      //case 10: kp = 42; break;  // '*'   // Uncomment this block for keypad4x3
      //case 11: kp = 48; break;  // '0'
      //case 12: kp = 35; break;  // '#'
      //default: kp += 48;

      case  1: kp = 49; break; // 1        // Uncomment this block for keypad4x4
      case  2: kp = 50; break; // 2
      case  3: kp = 51; break; // 3
      case  4: kp = 65; break; // A
      case  5: kp = 52; break; // 4
      case  6: kp = 53; break; // 5
      case  7: kp = 54; break; // 6
      case  8: kp = 66; break; // B
      case  9: kp = 55; break; // 7
      case 10: kp = 56; break; // 8
      case 11: kp = 57; break; // 9
      case 12: kp = 67; break; // C
      case 13: kp = 42; break; // *
      case 14: kp = 48; break; // 0
      case 15: kp = 35; break; // #
      case 16: kp = 68; break; // D
      

    }
    
    if (kp == oldkp)
    {return;}
    
     oldkp = kp;
    
    if (kp == 'A')
       {
       kujjehmode = 1;
       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       lcd_out(1,1,"Opening Request");
       delay_ms(2000);
       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       lcd_out(1,1,"Enter Password: ");
       for (i = 0; i < 20; i++)
           {
            scratch = 10 + i;
            internalpasswordarray[i] = eeprom_read(scratch);
            externalpasswordarray[i] = 0;
           }
       passwordpointer = 0;
       }
    else if (kp == 'B')
       {
       kujjehmode = 2;
       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       lcd_out(1,1,"PW Ch. Request");
       delay_ms(2000);
       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       lcd_out(1,1,"Enter Old PW: ");
       for (i = 0; i < 20; i++)
           {
            scratch = 10 + i;
            internalpasswordarray[i] = eeprom_read(scratch);
            externalpasswordarray[i] = 0;
           }
       passwordpointer = 0;
       }
    else if (kp == 'C')
       {
       kujjehmode = 3;

       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       lcd_out(1,1,"Content Request");
       delay_ms(2000);
       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       lcd_out(1,1,"Enter Password: ");
       for (i = 0; i < 20; i++)
           {
            scratch = 10 + i;
            internalpasswordarray[i] = eeprom_read(scratch);
            externalpasswordarray[i] = 0;
           }
       passwordpointer = 0;
       }
       /*else if (kp == 'D')
       {
       //kujjehmode = 4;
       }*/
    else if (kp == '#')
       {
       lcd_cmd(_LCD_CLEAR);
        lcd_cmd(_LCD_RETURN_HOME);
       lcd_out(1,1,"Return to M 0");
       delay_ms(2000);
       lcd_cmd(_LCD_CLEAR);
       lcd_cmd(_LCD_RETURN_HOME);
       passwordpointer = 0;
       kujjehmode = 0;
       }
    else
       {
           if (kujjehmode == 1)
           {
              if (kp == 'D')
              {
                if (passwordpointer > 0)
                   {
                   passwordpointer--;
                   externalpasswordarray[passwordpointer] = 0;

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                   }
              }
                 else if ((kp >= 48)&&(kp <= 57))
                 {
                  externalpasswordarray[passwordpointer] = kp;
                  if (passwordpointer < 17)
                     {passwordpointer++;}

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                 }
              else if(kp == '*')
                 {
                 if (strcmp(internalpasswordarray,externalpasswordarray) == 0)
                    {
                     //activate kujjeh solenoid
                     
                     delay_ms(1000);
                     
                     //deactivate kujjeh solenoid
                     lcd_cmd(_LCD_CLEAR);
                     lcd_cmd(_LCD_RETURN_HOME);
                     lcd_out(1,1,"Kujjeh Opened   ");
                     
                     solenoid = 1;
                     delay_ms(500);
                     solenoid = 0;
                     
                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,"Withdrawal:");
                     for (withdrawalpointer = 0; withdrawalpointer < 16; withdrawalpointer++)
                         {
                         withdrawalstring[withdrawalpointer] = 0;
                         };
                     withdrawalpointer = 0;
                     
                     kujjehmode = 12;
                     
                    }
                    else
                    {
                    lcd_cmd(_LCD_CLEAR);
                    lcd_cmd(_LCD_RETURN_HOME);
                    lcd_out(1,1,"Wrong Password");
                    buzzer = 1;
                    delay_ms(5000);
                    buzzer = 0;
                    }
                    delay_ms(2000);
                    //lcd_cmd(_LCD_CLEAR);
                    passwordpointer = 0;
                    //kujjehmode = 0;

                 };
           }
           else if (kujjehmode == 2)
           {
              if (kp == 'D')
                 {
                   if (passwordpointer > 0)
                     {
                     passwordpointer--;
                     externalpasswordarray[passwordpointer] = 0;

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                     };
                 }
              else if ((kp >= 48)&&(kp <= 57))
                 {
                  externalpasswordarray[passwordpointer] = kp;
                  if (passwordpointer < 17)
                     {passwordpointer++;}

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                 }
              else if(kp == '*')
                 {
                 if (strcmp(internalpasswordarray,externalpasswordarray) == 0)
                    {
                     //activate kujjeh solenoid

                     delay_ms(1000);

                     //deactivate kujjeh solenoid
                     lcd_cmd(_LCD_CLEAR);
                     lcd_cmd(_LCD_RETURN_HOME);
                     lcd_out(1,1,"Enter New PW");
                     for (i = 0; i < 20; i++)
                         {externalpasswordarray[i] = 0;};
                     passwordpointer = 0;
                     kujjehmode = 10;
                    }
                    else
                    {
                    lcd_cmd(_LCD_CLEAR);
                    lcd_cmd(_LCD_RETURN_HOME);
                    lcd_out(1,1,"Wrong Password");
                    
                    buzzer = 1;
                    delay_ms(5000);
                    buzzer = 0;
                    
                    delay_ms(2000);
                    lcd_cmd(_LCD_CLEAR);
                    lcd_cmd(_LCD_RETURN_HOME);
                    passwordpointer = 0;
                    kujjehmode = 0;
                    }

                 };

           }
           else if (kujjehmode == 3)
           {
              if (kp == 'D')
                 {
                  if (passwordpointer > 0)
                     {
                     passwordpointer--;
                     externalpasswordarray[passwordpointer] = 0;

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                     };
                 }
              else if ((kp >= 48)&&(kp <= 57))
                 {
                     externalpasswordarray[passwordpointer] = kp;
                     if (passwordpointer < 17)
                     {passwordpointer++;}

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                 }
              else if(kp == '*')
                 {
                 if (strcmp(internalpasswordarray,externalpasswordarray) == 0)
                    {
                     //activate kujjeh solenoid

                     delay_ms(1000);

                     //deactivate kujjeh solenoid
                     lcd_cmd(_LCD_CLEAR);
                     lcd_cmd(_LCD_RETURN_HOME);
                     lcd_out(1,1,"Content:  ");

                     lcd_out(2 ,1 , "You have now:");
                     longtostr(oldstate,scratchstring);
                     lcd_out(3 ,1 ,clearstring);
                     lcd_out(3 ,1 , scratchstring);
                     };
                 };
           }
           else if (kujjehmode == 4)
           {

           }
           else if (kujjehmode == 10)
           {
              if (kp == 'D')
                 {
                 if (passwordpointer > 0)
                    {
                    passwordpointer--;
                    externalpasswordarray[passwordpointer] = 0;

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                    };
                 }
              else if ((kp >= 48)&&(kp <= 57))
                 {
                  externalpasswordarray[passwordpointer] = kp;
                  if (passwordpointer < 17)
                     {passwordpointer++;}

                     lcd_out(2,1,clearstring);
                     lcd_out(2,1,externalpasswordarray);
                     delay_ms(200);
                 }
              else if(kp == '*')
                 {
                  if(passwordpointer == 0)
                    {
                      lcd_cmd(_LCD_CLEAR);
                      lcd_cmd(_LCD_RETURN_HOME);
                      lcd_out(1,1,"Password Reset");
                      lcd_out(2,1,"PW: 12345");
                      for (i = 0; i < 20; i++)
                          {
                          externalpasswordarray[i] = 0;
                          }
                      externalpasswordarray[0] = '1';
                      externalpasswordarray[1] = '2';
                      externalpasswordarray[2] = '3';
                      externalpasswordarray[3] = '4';
                      externalpasswordarray[4] = '5';
                       for (i = 0; i < 20; i++)
                           {
                           eeprom_write((i + 10),externalpasswordarray[i]);
                           delay_ms(20);
                           };
                      delay_ms(2000);
                      lcd_cmd(_LCD_CLEAR);
                      kujjehmode = 0;
                    }
                  else
                    {
                       lcd_cmd(_LCD_CLEAR);
                       lcd_cmd(_LCD_RETURN_HOME);
                       lcd_out(1,1,"Password Changed");
                       for (i = 0; i < 20; i++)
                           {
                           eeprom_write((i + 10),externalpasswordarray[i]);
                           delay_ms(20);
                           };

                      delay_ms(2000);
                      lcd_cmd(_LCD_CLEAR);
                      lcd_cmd(_LCD_RETURN_HOME);

                      passwordpointer = 0;
                      kujjehmode = 0;
                    }
                 };
           }
           else if(kujjehmode == 12)
           {
              if (kp == 'D')
                 {
                 if (withdrawalpointer > 0)
                    {
                    withdrawalpointer--;
                    withdrawalstring[withdrawalpointer] = 0;

                    lcd_out(3,1,clearstring);
                    lcd_out(3,1,withdrawalstring);
                    delay_ms(200);
                    };
                 }
              else if ((kp >= 48)&&(kp <= 57))
                 {
                  withdrawalstring[withdrawalpointer] = kp;
                  if (withdrawalpointer < 12)
                     {withdrawalpointer++;}

                     lcd_out(3,1,clearstring);
                     lcd_out(3,1,withdrawalstring);
                     delay_ms(200);
                 }
              else if (kp == 'D')
                 {
                 for (withdrawalpointer = 0; withdrawalpointer < 16; withdrawalpointer++)
                     {
                     withdrawalstring[withdrawalpointer] = 0;
                     }
                 withdrawalpointer = 0;
                 lcd_out(3,1,clearstring);
                 lcd_out(3,1,withdrawalstring);
                 }

              else if(kp == '*')
                 {
                 lcd_cmd(_LCD_CLEAR);
                 lcd_cmd(_LCD_RETURN_HOME);
                 if (strcmp("00000",withdrawalstring) == 0)
                      {
                       lcd_out(1,1,"Content = 0");
                       oldstate = 0;
                       storeineeprom();
                       }
                 else if(strcmp("0",withdrawalstring) == 0)
                       {
                       lcd_out(1,1,"Withdrawal = 0");
                       }
                 else
                       {
                        withdrawalvalue = atol(withdrawalstring);
                        loadfromeeprom();
                        oldstate = oldstate - withdrawalvalue;
                        if (oldstate < 0)
                           {
                           oldstate = 0;
                           }
                        storeineeprom();
                        lcd_out(1,1,"Rem Content");
                        longtostr(oldstate,scratchstring);
                        lcd_out(2,1,scratchstring);
                       }
                       
                       delay_ms(2000);
                       
                       lcd_cmd(_LCD_CLEAR);
                       lcd_cmd(_LCD_RETURN_HOME);
                       
                  kujjehmode = 0;
                 };
           }
       }
}

long checkinputquantity(void)
    {
     char alpha[16];
     int j;
     int pointer = 0;
     char inputfromkeypad = 0;

     
     for (j = 0; j < 16; j++)
         {
          alpha[j] = 0;
         }

     while (inputfromkeypad != '*')
           {
           inputfromkeypad = keypadkeycheck();
           if (inputfromkeypad == '#')
              {
              for (j = 0; j < 16; j++)
                 {
                  alpha[j] = 0;
                 }
                pointer = 0;
                lcd_out(3,1,clearstring);
              }
           else if((inputfromkeypad == 'D')&&(inputfromkeypad != oldkp2))
              {
               if (pointer > 0)
                  {
                  pointer--;
                  alpha[pointer] = 0;

                  lcd_out(3,1,clearstring);
                  lcd_out(3,1,alpha);
                  delay_ms(200);
                  };
              }
           else if ((inputfromkeypad >= 48)&&(inputfromkeypad <= 57)&& (inputfromkeypad != oldkp2))
              {
              

              alpha[pointer] = inputfromkeypad;
              if (pointer < 13)
                 {
                 pointer++;
                 }
              lcd_out(3,1,clearstring);
              lcd_out(3,1,alpha);
              delay_ms(200);
              }
              
             oldkp2 = inputfromkeypad;
           }
       oldkp2 = 0;

       return  atol(alpha);
    }

char keypadkeycheck(void)
     {
