library(ggplot2)
library(scagnostics)

rootDirectory <- "C:/Users/Elvis Lei/Documents/scagnostics_data/"
issueDirectory <- "C:/Users/Elvis Lei/Documents/scagnostics_data/issue/"
outDirectory <- "C:/Users/Elvis Lei/Documents/scagnostics_data/issue/rotate/"
suffix <- ".csv"
issueName <- "/issue_2.csv"

point_size = 1.5
alpha = 0.55
shape = 20
col = "black"

issueFile <- paste(issueDirectory, issueName, sep = "")

fileName <- readLines(issueFile)

auto_rotate_plot <- function(filename, angle, head, outPngName, outCSVName, outDataName)
{
  
  data <- read.csv(filename, header = head)
  
  x <- data[[1]]
  y <- data[[2]]
  
  backup_y <- y
  
  rx <- max(x) - min(x)
  ry <- max(y) - min(y)
  
  y <- y * (rx / ry)
  
  backupAngle <- angle
  
  angle <- angle * pi / 180
  
  x0 <- min(x) + (max(x) - min(x))/2
  y0 <- min(y) + (max(y) - min(y))/2
  
  x1 <- (x - x0)*cos(angle) - (y - y0)*sin(angle) + x0
  y1 <- (x - x0)*sin(angle) + (y - y0)*cos(angle) + y0
  
  x <- x1
  y <- y1
  
  data_frame <- data.frame(x, y)
  
  p <- ggplot(data_frame, aes(x, y)) 
  p <- p + geom_point(size = point_size, shape = shape, col = col, alpha = alpha)
  p <- p + theme(axis.text.y = element_blank(), axis.text.x = element_blank())
  p <- p + theme(axis.title = element_blank())
  p <- p + ggtitle(paste(filename, as.character(backupAngle), sep = " "))
  
  ggsave(plot = p, filename = outPngName, width = 3, height = 3)
  
  data_frame <- data.frame(x, y)
  
  result <- scagnostics(data_frame)

  result <- c(result) 
  
  write.table(result,
              file = outCSVName,
              append = FALSE, 
              quote = FALSE, 
              sep = ",", 
              col.names = FALSE, 
              row.names = c("Outlying", "Skewed", "Clumpy", "Sparse", "Striated", "Convex", "Skinny", "Stringy", "Monotonic"))
  
  data_frame <- data.frame(x, y)

  write.table(data_frame,
              file = outDataName,
              append = FALSE,
              quote = TRUE,
              sep = ",",
              col.names = FALSE,
              row.names = FALSE) 
  
}

batch_process_filename <- function(filename)
{
  fileLength <- length(filename)
  for(item in seq(1, fileLength))
  {
    fileName <- filename[item] 
    outName <- gsub("%20", " ", x = fileName)
    outName <- gsub("png", "csv", x = outName)
    outName <- gsub("file:///", "", x = outName)
    filename[item] <- outName
  }
  return(filename)
}

fileName <- as.vector(fileName)
fileName <- batch_process_filename(fileName)

angleSet <- c(1, 5, 15, 45, 180)

for(iteratorFileName in fileName)
{
  for(i in seq(0, length(angleSet)))
  {
    
    angle <- angleSet[i]
    
    temp <- gsub(rootDirectory, "", iteratorFileName)
    temp <- gsub(suffix, "", temp)
    
    subDirectory <- temp
    
    outNamePrefix <- paste(outDirectory, subDirectory, "/", sep = '')
    tempList <- strsplit(temp, split = "/")
    
    type <- tempList[[1]][1]
    name <- tempList[[1]][2]
    
    if(!dir.exists(outNamePrefix))
    {
      middleDirectory <- paste(outDirectory, type, "/", sep = "")
      if(!dir.exists(middleDirectory))
      {
        dir.create(middleDirectory)      
      }
      dir.create(outNamePrefix) 
      
      dir.create(paste(outNamePrefix, "/csv/", sep = ""))
      dir.create(paste(outNamePrefix, "/png/", sep = ""))
      dir.create(paste(outNamePrefix, "/result/", sep = ""))
      dir.create(paste(outNamePrefix, "/html/", sep = ""))
    }
    
    outPngName <- paste(outNamePrefix, 
                        "/png/",
                        name,
                        "_picture_", 
                        as.character(i),
                        "_angle_", 
                        as.character(angle),
                        ".png", 
                        sep = "")
    outCSVName <- paste(outNamePrefix, 
                        "/result/",
                        name, 
                        "_picture_", 
                        as.character(i),
                        "_angle_",
                        as.character(angle),
                        ".csv", 
                        sep = "")
    outDataName <- paste(outNamePrefix, 
                         "/csv/",
                         name, 
                         "_picture_", 
                         as.character(i), 
                         "_angle_",
                         as.character(angle),
                         ".csv", 
                         sep = "")
    if(i == 0)
    {
      auto_rotate_plot(iteratorFileName, 0, FALSE, outPngName, outCSVName, outDataName) 
    }
    else
    {
      auto_rotate_plot(iteratorFileName, angle, FALSE, outPngName, outCSVName, outDataName)
    }
  }
}
