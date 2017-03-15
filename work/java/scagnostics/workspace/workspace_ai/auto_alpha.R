library(ggplot2)
library(scagnostics)

inputCSV <- paste(directory, originName, ".csv", sep = "")
pngName <- paste(outputDirectory, originName, ".png", sep = "")
alphaHullInfo <- "./alphaHull.csv"

width <- 320
height <- 320

lwdAlpha = 3

col = ""

flag <- grep("rate_0.2", originName, value = F)
if(length(flag) != 0)
{
    col = "blue"
}

flag <- grep("rate_0.01", originName, value = F)
if(length(flag) != 0)
{
    col = "black"
}

flag <- grep("rate_0.05", originName, value = F)
if(length(flag) != 0)
{
    col = "red"
}

axes <- FALSE

xlab <- ""
ylab <- ""

colAlpha <- "purple"

cex <- 2
pch <- 20

data <- read.csv(inputCSV, head = FALSE)
# alpha <- read.csv(alphaHullInfo, head = FALSE, sep = ',')

alpha <- tryCatch({
    read.csv(alphaHullInfo, head = FALSE, sep = ',')
}, error = function(e){return(data.frame(c(), c()))})

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

# p <- ggplot(data_frame, aes(x, y))
# p <- p + geom_point(size = point_size, shape = shape, col = col, alpha = alpha)
# p <- p + theme(axis.text.y = element_blank(), axis.text.x = element_blank())
# p <- p + theme(axis.title = element_blank())



png(pngName, width = width, height = height)

plot(data_frame, pch = pch, col = col, cex = cex, axes = axes, xlab = xlab , ylab = ylab, asp = 1)

if(length(alpha) != 0)
{
    alpha_x <- alpha[[1]]
    alpha_y <- alpha[[2]]
    for(item in seq(1, length(alpha_x), 2))
    {

        start_x <- alpha_x[item]
        start_x <- get_real_value(mean_x, max_x, min_x, start_x)

        start_y <- alpha_y[item]
        start_y <- get_real_value(mean_y, max_y, min_y, start_y)

        end_x <- alpha_x[item+1]
        end_x <- get_real_value(mean_x, max_x, min_x, end_x)

        end_y <- alpha_y[item+1]
        end_y <- get_real_value(mean_y, max_y, min_y, end_y)

        # lines(c(start_x, start_y), c(end_x, end_y))

        segments(start_x, start_y, end_x, end_y, col = colAlpha, lwd = lwdAlpha)

    }
}
dev.off()
