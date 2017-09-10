void setup() {
  Serial.begin(9600);
  while (!Serial) {};  
}

void read_command(char *commandline) {
  char lastchar = "0";
  byte linecount = 0;
  while (1) {
    if (Serial.available() > 0) {
      lastchar = Serial.read();
      commandline[linecount] = lastchar;
      Serial.print(lastchar);
      linecount++;
    }    
    if (lastchar == '\r') {
      Serial.println();
      lastchar = "0";
      break;
    } 
  }
}

void parse_command(char *commandline) {
  char command[10];
  char opts[40];
  char n = '0';
  byte i = 0, j = 0;

  while (commandline[i] != ' ') {
    command[j] = commandline[i];
    i++;
    j++;    
    if (commandline[i] == 0) break; 
  }
  j = 0;
  
  while (commandline[i] != '\r') {
    opts[j] = commandline[i];
    j++;
    i++;
    if (commandline[i] == 0) break;
  }

  Serial.print("$ > GOT COMMAND: ");
  Serial.print(command);
  Serial.println();
  Serial.print("$ > GOT OPTIONS: ");
  Serial.print(opts);
  Serial.println();
  memset(opts, 0, sizeof(opts));
  memset(command, 0, sizeof(command));
}

char line[100];

void loop() {  
  Serial.print("$ > ");
  read_command(line);
  parse_command(line);  
  memset(line, 0, sizeof(line));
}

