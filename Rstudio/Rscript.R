setwd("D:/RTES1-master/code_v_0.1")

#Advanced
advanced_delay <- c()
advanced <- c()
data = read.csv("advancedResults.txt", header = FALSE)
advanced = data[,1]
rm(data)

for ( i in (1:(length(advanced)-1))) {
  advanced_delay[i] = advanced[i+1] - advanced[i]
}

#x11();plot( advanced_delay, type="p" , bty="o" , xlab="TIMESTAMP'S   index" , ylab="DELAY    Value   (MICRO SECONDS)" ,
#      col=rgb(0.2,0.4,0.1,0.7) , pch= 20, col.lab = "black" )
#x11();plot( advanced, type = "l", bty = "o",  xlab="TIMESTAMP'S   index" , ylab="TIMESTAMP'S    Value   (MICRO SECONDS)",
#      col=rgb(0.2,0.4,0.1,0.7) , pch=1, col.lab = "black")
bins <- cut(advanced_delay,100)
x11();plot( bins, xlab="DELAY VALUES(USEC)" , ylab="OCCURENCES")

mean(advanced_delay)
sd(advanced_delay)
advanced_execution_time = advanced[length(advanced)] - advanced[1]
print(advanced_execution_time, digits = 16)

#Simple
simple_delay <- c()
simple <- c()
data = read.csv("simpleResults.txt", header = FALSE)
simple = data[,1]
rm(data)

for ( i in (1:(length(simple)-1))) {
  simple_delay[i] = simple[i+1] - simple[i]
}

x11();plot( simple_delay, type="p" , bty="o" , xlab="TIMESTAMP'S   index" , ylab="DELAY    Value   (MICRO SECONDS)" ,
      col=rgb(0.2,0.4,0.1,0.7) , pch=1, col.lab = "black" )
x11();plot( simple, type = "l", bty = "o",  xlab="TIMESTAMP'S   index" , ylab="TIMESTAMP'S    Value   (MICRO SECONDS)",
      col=rgb(0.2,0.4,0.1,0.7) , pch=1, col.lab = "red")
mean(simple_delay)
sd(simple_delay)
simple_execution_time = simple[length(advanced)] - simple[1]
print(simple_execution_time, digits = 16)
