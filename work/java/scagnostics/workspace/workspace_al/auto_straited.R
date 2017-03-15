library(ggplot2)
library(scagnostics)

if(0)
{
    pngName <- paste(outputDirectory, originName, "_alpha", ".png", sep = "")
    alphaHullInfo <- "./alphaHull.csv"

    width <- 320
    height <- 320

    lwdAlpha = 2

    col <- "blue"
    axes <- FALSE

    xlab <- ""
    ylab <- ""

    colAlpha <- "purple"

    cex <- 2
    pch <- 20

    data <- read.csv(inputCSV, head = FALSE)
    alpha <- read.csv(alphaHullInfo, head = FALSE, sep = ',')

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

    alpha_x <- alpha[[1]]
    alpha_y <- alpha[[2]]

    png(pngName)

    plot(data_frame, pch = pch, col = col, cex = cex, axes = axes, xlab = xlab , ylab = ylab, asp = 1)

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
    dev.off()
}

outputCSVName <- paste(outputDirectory, originName, ".csv", sep = "")
file.copy("./striated.csv", outputCSVName)

