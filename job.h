#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QRunnable>

#include "jobresult.h"

class Job : public QObject, public QRunnable {
  Q_OBJECT
public:
  Job(QObject *parent = 0);
  void run() override;

  void setAreaSize(const QSize &areaSize);

  void setPixelPositionY(int pixelPositionY);

  void setMoveOffset(const QPointF &moveOffset);

  void setScaleFactor(double scaleFactor);

  void setIterationMax(int iterationMax);

signals:
  void jobCompleted(JobResult JobResult);

public slots:
  void abort();

private:
  QAtomicInteger<bool> mAbort;
  QSize mAreaSize;
  int mPixelPositionY;
  QPointF mMoveOffset;
  double mScaleFactor;
  int mIterationMax;
};

#endif // JOB_H
