percivaldataframe <- data.frame()
logpercivalfilename <- "//greenfinch/$Team/Public/TimS/HOBO_Data/GG4400_percivals.csv"

readHOBOFile <- function(logpercivalfilename){
  percivaldataframe <<- fread(logpercivalfilename)
  percivaldataframe <<- data.frame(percivaldataframe)   
  percivaldataframe<<-percivaldataframe[,-c(36:52)]
  colnames(percivaldataframe) <<- c("Date_Time","B_Desk_Temp","B_Desk_RH","16-08_Temp","16-08_RH","13-03_Temp","13-03_RH","13-08_Temp","13-08_RH","13-07_Temp","13-07_RH","13-04_Temp","13-04_RH","13-06_Temp","13-06_RH","13-05_Temp","13-05_RH","16-09_Temp","16-09_RH","16-10_Temp","16-10_RH","17-01_Temp","17-01_RH","17-02_Temp","17-02_RH","16-04_Temp","16-04_RH","16-05_Temp","16-05_RH","16-03_Temp","16-03_RH","16-02_Temp","16-02_RH","16-01_Temp","16-01_RH")
  #print(length(colnames(df)))
  percivaldataframe$Date_Time<<- strptime(percivaldataframe$Date_Time, "%m/%d/%y %H:%M")
}