library(ggplot2)
library(scagnostics)

inputCSV <- paste(directory, originName, ".csv", sep = "")
pngName <- paste(outputDirectory, originName, ".png", sep = "")
DTInfo <- "./DT.csv"

width <- 512
height <- 512

lwdDT <- 2
col <- "blue"
axes <- FALSE

xlab <- ""
ylab <- ""

colDT <- "purple"

cex <- 1.5 
pch <- 20

data <- read.csv(inputCSV, head = FALSE)
DT <- read.csv(DTInfo, head = FALSE, sep = ',')

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

DT_x <- DT[[1]]
DT_y <- DT[[2]]

png(pngName)

plot(data_frame, pch = pch, col = col, cex = cex, axes = axes, xlab = xlab , ylab = ylab)

for(item in seq(1, length(DT_x), 2))
{

    start_x <- DT_x[item]
    start_x <- get_real_value(mean_x, max_x, min_x, start_x)

    start_y <- DT_y[item]
    start_y <- get_real_value(mean_y, max_y, min_y, start_y)

    end_x <- DT_x[item+1]
    end_x <- get_real_value(mean_x, max_x, min_x, end_x)

    end_y <- DT_y[item+1]
    end_y <- get_real_value(mean_y, max_y, min_y, end_y)

    # lines(c(start_x, start_y), c(end_x, end_y))

    segments(start_x, start_y, end_x, end_y, col = colDT, lwd = lwdDT)
}

dev.off()
