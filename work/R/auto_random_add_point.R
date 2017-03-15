library(ggplot2)
library(scagnostics)

rootDirectory <- "C:/Users/Elvis Lei/Documents/scagnostics_data/"
issueDirectory <- "C:/Users/Elvis Lei/Documents/scagnostics_data/issue/"
outDirectory <- "C:/Users/Elvis Lei/Documents/scagnostics_data/issue/new_add_point/"
suffix <- ".csv"
issueName <- "/issue.csv"

point_size = 1.5
alpha = 0.5
shape = 20

col_1 = "black"
col_2 = "red"
col_3 = "blue"

issueFile <- paste(issueDirectory, issueName, sep = "")

fileName <- readLines(issueFile)

auto_add_plot <- function(filename, addRate, head, outPngName, outCSVName, outDataName, color)
{

    data <- read.csv(filename, header = head)

    x <- data[[1]]
    y <- data[[2]]

    rx <- max(x) - min(x)
    ry <- max(y) - min(y)

    backup_y <- y

    y <- y * (rx / ry)

    max_x <- max(x)
    max_y <- max(y)

    min_x <- min(x)
    min_y <- min(y)

    size <- length(x)

    label_1 <- rep(1, size)

    addNumber <- as.integer(size * addRate)

    add_x <- runif(addNumber, min_x, max_x)
    add_y <- runif(addNumber, min_y, max_y)

    label_2 <- rep(2, addNumber)

    label <- c(label_1, label_2)
    backup_label <- label

    x <- c(x, add_x)
    y <- c(y, add_y)

    data_frame <- data.frame(x, y, label)
    data_frame$label <- factor(data_frame$label)

    p <- ggplot(data_frame, aes(x = x, y = y, colour = label)) 
    p <- p + geom_point(size = point_size, shape = shape, col = color, alpha = alpha)
    p <- p + theme(axis.text.y = element_blank(), axis.text.x = element_blank())
    p <- p + theme(axis.title = element_blank())
    # p <- p + ggtitle(paste(filename, paste(as.character(addRate * 100), "%", sep = ""), sep = "     "))

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

    data_frame <- data.frame(x, y, backup_label)

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
if(0)
{
    for(iteratorFileName in fileName)
    {
        pictureNumber = 50
        addRate = 0.01

        print(addRate)
        print(iteratorFileName)

        for(i in seq(0, pictureNumber))
        {

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
                                "_rate_", 
                                as.character(addRate),
                                ".png", 
                                sep = "")
            outCSVName <- paste(outNamePrefix, 
                                "/result/",
                                name, 
                                "_picture_", 
                                as.character(i),
                                "_rate_",
                                as.character(addRate),
                                ".csv", 
                                sep = "")
            outDataName <- paste(outNamePrefix, 
                                 "/csv/",
                                 name, 
                                 "_picture_", 
                                 as.character(i), 
                                 "_rate_",
                                 as.character(addRate),
                                 ".csv", 
                                 sep = "")
            if(i == 0)
            {
                auto_add_plot(iteratorFileName, 0, FALSE, outPngName, outCSVName, outDataName, col_1) 
            }
            else
            {
                auto_add_plot(iteratorFileName, addRate, FALSE, outPngName, outCSVName, outDataName, col_1)
            }
        }
    }
}

if(0)
{
    for(iteratorFileName in fileName)
    {
        pictureNumber = 50
        addRate = 0.05

        print(addRate)
        print(iteratorFileName)

        for(i in seq(1, pictureNumber))
        {

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
                                "_rate_", 
                                as.character(addRate),
                                ".png", 
                                sep = "")
            outCSVName <- paste(outNamePrefix, 
                                "/result/",
                                name, 
                                "_picture_", 
                                as.character(i),
                                "_rate_",
                                as.character(addRate),
                                ".csv", 
                                sep = "")
            outDataName <- paste(outNamePrefix, 
                                 "/csv/",
                                 name, 
                                 "_picture_", 
                                 as.character(i), 
                                 "_rate_",
                                 as.character(addRate),
                                 ".csv", 
                                 sep = "")
            auto_add_plot(iteratorFileName, addRate, FALSE, outPngName, outCSVName, outDataName, col_2)
        }
    }
}

if(1)
{
    for(iteratorFileName in fileName)
    {
        pictureNumber = 50
        addRate = 0.2

        print(addRate)
        print(iteratorFileName)

        for(i in seq(1, pictureNumber))
        {

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
                                "_rate_", 
                                as.character(addRate),
                                ".png", 
                                sep = "")
            outCSVName <- paste(outNamePrefix, 
                                "/result/",
                                name, 
                                "_picture_", 
                                as.character(i),
                                "_rate_",
                                as.character(addRate),
                                ".csv", 
                                sep = "")
            outDataName <- paste(outNamePrefix, 
                                 "/csv/",
                                 name, 
                                 "_picture_", 
                                 as.character(i), 
                                 "_rate_",
                                 as.character(addRate),
                                 ".csv", 
                                 sep = "")
            auto_add_plot(iteratorFileName, addRate, FALSE, outPngName, outCSVName, outDataName, col_3)
        }
    }
}
