#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QThread>
#include <QVideoFrame>
#include <QWidget>

class FrameProcess : public QObject
{
  Q_OBJECT
public slots:
  void processFrame(QVideo frame , int levels);
signals:
  void histogramRead(QVector<qreal> histogram);
};

class HistogramWidget : public QWidget
{
  Q_OBJECT
public:
  explicit HistogramWidget(QWidget * parent = 0);
  virtual ~HistogramWidget();
  void setLevels(int levels){m_levels = levels;}
public slots:
  void processFrame(QVideoFrame frame);
  void setHistogram(QVector<qureal> histogram);
protected:
  void paintEvent(QPaintEvent *event);
private:
  QVector<qreal> m_histogram;
  int m_levels;
  FrameProcess m_processor;
  QTread m_processThread;
  bool m_isBusy;
};

#endif // HISTOGRAMWIDGET_H
