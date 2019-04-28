rm(list = ls())
setwd("C:/Users/dimit/Desktop/code_v_0.1")
library(stringr)
us <- c();
sy <- c();
ni <- c();
id <- c();
wa <- c();
hi <- c();
si <- c();
st <- c();
CPU <- c();
state <- c();

con = file("log.txt", "r");
lines = readLines(con);


counter <- 1
for (i in seq( 1, length(lines), by = 2)) {
  #extract us
  temp = str_extract(lines[i], "\\d+.\\d+ us")
  tempus = str_extract(temp, "\\d+.\\d+")
  us[counter] = tempus;
  
  #extract sy
  temp = str_extract(lines[i], "\\d+.\\d+ sy")
  tempsy = str_extract(temp, "\\d+.\\d+")
  sy[counter] = tempsy
  
  #extract ni
  temp = str_extract(lines[i], "\\d+.\\d+ ni")
  tempni = str_extract(temp, "\\d+.\\d+")
  ni[counter] = tempni
  
  #extract id
  temp = str_extract(lines[i], "\\d+.\\d+ id")
  tempid = str_extract(temp, "\\d+.\\d+")
  id[counter] = tempid
  
  #extract wa
  temp = str_extract(lines[i], "\\d+.\\d+ wa")
  tempwa = str_extract(temp, "\\d+.\\d+")
  wa[counter] = tempwa
  
  #extract hi
  temp = str_extract(lines[i], "\\d+.\\d+ hi")
  temphi = str_extract(temp, "\\d+.\\d+")
  hi[counter] = temphi
  
  #extract si
  temp = str_extract(lines[i], "\\d+.\\d+ si")
  tempsi = str_extract(temp, "\\d+.\\d+")
  si[counter] = tempsi
  
  #extract st
  temp = str_extract(lines[i], "\\d+.\\d+ st")
  tempst = str_extract(temp, "\\d+.\\d+")
  st[counter] = tempst
  
  counter = counter + 1;
      
}

us <- as.double(us)
sy <- as.double(sy)
ni <- as.double(ni)
id <- as.double(id)
wa <- as.double(wa)
hi <- as.double(hi)
si <- as.double(si)
st <- as.double(st)

counter = 1
for(i in seq( 2, length(lines), by = 2)){
  
  #extract state
  temp = str_extract(lines[i], " [:upper:] ")
  state[counter] = str_extract(temp,"\\w")
  
  #extract CPU
  CPU[counter] <- str_extract( lines[i], "\\d+\\.\\d+") #extract fisrt string "digits.digits" => CPU 

  counter = counter + 1
}

CPU <- as.double(CPU)

close(con)

#plot id
plot(id, type = "p", pch = 21, col = "green", xlab = "indeces", ylab = "Idle percentage of the executable process")
boxplot(id, col = "green", main = "Idle Percentage Boxplot of the executable process")
