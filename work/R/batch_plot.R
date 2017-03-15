library("rJava")
library("scagnostics")
library("ggplot2")

options(scipen = 10000)

directory <- "./thousand_csv/csv/"
out_directory <- "./thousand_csv/result/"
png_directory <- "./thousand_csv/png/"

filelist <- list.files(directory)
count <- 0

for (filename in filelist)
{
  data <- read.csv(paste(directory, filename, sep = ''), header = FALSE)
  
  out_name <- paste(out_directory, filename, sep = '')
  
  out_png_name <- paste(png_directory, filename, ".png", sep = '' )
  out_png_name <- gsub(".csv", ".png", out_name, fixed = TRUE)
  out_png_name <- gsub("result", "png", out_png_name, fixed = TRUE)
 
  x <- data[[1]]
  y <- data[[2]]
  
  range_x <- max(x) - min(x)
  range_y <- max(y) - min(y)
  
  if(range_y == 0)
  {
    print("REMOVE THE FILE > ") 
    print(filename)
    file.remove(paste(directory, filename, sep = '')) 
    next() 
  }
  
  y <- y * range_x / range_y
  
  data_frame <- data.frame(x, y)
  
  print(out_png_name)
  print(out_name)
  
  # png(filename = out_png_name, width = 512, height = 512)

  p <- ggplot(data_frame, aes(x, y)) 
  p <- p + geom_point(size = 3, shape = 20, col="black", alpha = 0.65)
  p <- p + theme(axis.text.y = element_blank(), axis.text.x = element_blank())
  ggsave(plot = p, filename = out_png_name)
  
  # plot(data_frame)
  # dev.off()
  
  result <- scagnostics(data_frame)
  
  result <- c(result)
  
  write.table(result,
              file = out_name,
              append = FALSE, 
              quote = FALSE, 
              sep = ",", 
              col.names = FALSE, 
              row.names = c("Outlying", "Skewed", "Clumpy", "Sparse", "Striated", "Convex", "Skinny", "Stringy", "Monotonic"))
}