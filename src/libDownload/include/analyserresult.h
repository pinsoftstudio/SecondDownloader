#ifndef ANALYSERRESULT_H
#define ANALYSERRESULT_H

#include <QDialog>
#include "analyser.h"
namespace Ui {
class AnalyserResult;
}

class AnalyserResult : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyserResult(QString filePath, QWidget *parent = nullptr);
    ~AnalyserResult();
private:
    Ui::AnalyserResult *ui;
    Analyser *an;
    void cleanUp();
private slots:
    void onAnalyseFinished(QString result);
    void onAnalyseFailed();

};

#endif // ANALYSERRESULT_H
