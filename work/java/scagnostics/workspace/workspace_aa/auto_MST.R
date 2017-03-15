library(ggplot2)
library(scagnostics)

args <- commandArgs()

# directory <- args[6]
# originName <- args[7]
# outputDirectory <- args[8]

if(0)
{
    root <- "../../"
    firstDirectory <- "/java/"
    secondDirectory <- "/scagnostics/"
    fileOriName <- "rays_100_47__picture_0_rate_0.01"
    suffix <- ".csv"

    inputCSV <- paste(root,
                      firstDirectory,
                      sep = "")
    inputCSV <- paste(inputCSV, secondDirectory, sep = "")
    inputCSV <- paste(inputCSV,
                      fileOriName,
                      suffix,
                      sep = "")

    pngName <- paste(fileOriName, ".png", sep = "")
}

inputCSV <- paste(directory, originName, ".csv", sep = "")
pngName <- paste(outputDirectory, originName, ".png", sep = "")
MSTInfo <- "./MST.csv"

width <- 512
height <- 512


lwdMST <- 2
col <- "blue"
axes <- FALSE

xlab <- ""
ylab <- ""

colMST <- "purple"

cex <- 1.5 
pch <- 20

data <- read.csv(inputCSV, head = FALSE)
MST <- read.csv(MSTInfo, head = FALSE, sep = ',')

x <- data[[1]]
y <- data[[2]]

rx <- max(x) - min(x)
ry <- max(y) - min(y)

y <- y * rx / ry

mean_x <- mean(x)
mean_y <- mean(y)

max_x <- max(x)
min_x <- min(x)

max_y <- max(y)
min_y <- min(y)

get_real_value <-function(mean, max, min, value)
{
    return_value <- (value/1000) * (max - min) + min
}

data_frame <- data.frame(x, y)

MST_x <- MST[[1]]
MST_y <- MST[[2]]

png(pngName)

plot(data_frame, pch = pch, col = col, cex = cex, axes = axes, xlab = xlab , ylab = ylab)

for(item in seq(1, length(MST_x), 2))
{

    start_x <- MST_x[item]
    start_x <- get_real_value(mean_x, max_x, min_x, start_x)

    start_y <- MST_y[item]
    start_y <- get_real_value(mean_y, max_y, min_y, start_y)

    end_x <- MST_x[item+1]
    end_x <- get_real_value(mean_x, max_x, min_x, end_x)

    end_y <- MST_y[item+1]
    end_y <- get_real_value(mean_y, max_y, min_y, end_y)

    # lines(c(start_x, start_y), c(end_x, end_y))

    segments(start_x, start_y, end_x, end_y, col = colMST, lwd = lwdMST)
}

dev.off()
