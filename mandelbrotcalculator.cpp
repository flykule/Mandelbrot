#include "mandelbrotcalculator.h"
#include <QDebug>
#include <QThreadPool>

#include "job.h"

const int JOB_RESULT_THRESHOLD = 10;

MandelbrotCalculator::MandelbrotCalculator(QObject *parent)
    : QObject(parent), mMoveOffset(0.0, 0.0), mScaleFactor(0.0),
      mAreaSize(0, 0), mIterationMax(10), mReceivedJobResults(0), mJobResults(),
      mTimer() {}

void MandelbrotCalculator::generatePicture(QSize areaSize, QPointF moveOffset,
                                           double scaleFactor,
                                           int iterationMax) {
  if (areaSize.isEmpty()) {
    return;
  }

  mTimer.start();
  clearJobs();

  mAreaSize = areaSize;
  mMoveOffset = moveOffset;
  mScaleFactor = scaleFactor;
  mIterationMax = iterationMax;

  for (int pixelPostionY = 0; pixelPostionY < mAreaSize.height();
       ++pixelPostionY) {
    QThreadPool::globalInstance()->start(createJob(pixelPostionY));
  }
}

Job *MandelbrotCalculator::createJob(int pixelPositionY) {
  Job *job = new Job();

  job->setPixelPositionY(pixelPositionY);
  job->setMoveOffset(mMoveOffset);
  job->setScaleFactor(mScaleFactor);
  job->setAreaSize(mAreaSize);
  job->setIterationMax(mIterationMax);

  connect(this, &MandelbrotCalculator::abortAllJobs, job, &Job::abort);
  connect(job, &Job::jobCompleted, this, &MandelbrotCalculator::process);
  return job;
}

void MandelbrotCalculator::clearJobs() {
  mReceivedJobResults = 0;
  emit abortAllJobs();
  QThreadPool::globalInstance()->clear();
}
