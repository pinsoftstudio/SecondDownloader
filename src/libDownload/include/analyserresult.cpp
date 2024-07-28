#include "analyserresult.h"
#include "ui_analyserresult.h"

#include <QJsonObject>
#include <QJsonDocument>
AnalyserResult::AnalyserResult(QString filePath,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AnalyserResult)
{
    Qt::WindowFlags flags;
    ui->setupUi(this);setWindowFlags(flags|Qt::WindowCloseButtonHint|Qt::WindowStaysOnTopHint);

    an=new Analyser(filePath);
    connect(an,&Analyser::analyseFailed,this,&AnalyserResult::onAnalyseFailed);
    connect(an,&Analyser::analyseFinished,this,&AnalyserResult::onAnalyseFinished);
    an->start();


}

AnalyserResult::~AnalyserResult()
{
    delete ui;
}

void AnalyserResult::cleanUp()
{
    if(an->isRunning()){
        an->terminate();
        an->wait();
    }
    disconnect(an,&Analyser::analyseFailed,this,&AnalyserResult::onAnalyseFailed);
    disconnect(an,&Analyser::analyseFinished,this,&AnalyserResult::onAnalyseFinished);

    delete an;

}

void AnalyserResult::onAnalyseFinished(QString result)
{
    qint64 total=0;
    qint64 maliciousNum=0;
    qint64 undetected=0;
    QJsonDocument doc=QJsonDocument::fromJson(result.toUtf8());
    QJsonObject jsonObject=doc.object();
    QJsonValue dataValue = jsonObject.value("data");
    // QMessageBox::information(this,"",dataValue.toString());
    QJsonObject dataObject=dataValue.toObject();
    QJsonValue attrValue=dataObject.value("attributes");
    QJsonObject attrObject=attrValue.toObject();
    QJsonValue anValue=attrObject.value("last_analysis_stats");
    QJsonObject anObject=attrValue.toObject();
    for(auto it=anObject.constBegin();it!=anObject.constEnd();++it){
        if(it.value().isObject()){
            QJsonObject killerObject=it.value().toObject();
            for(auto jt=killerObject.constBegin();jt!=killerObject.constEnd();++jt){
                QJsonObject akiller=jt.value().toObject();
                QJsonValue categoryValue=akiller.value("category");
                QString strCategory=categoryValue.toString();
                if(strCategory=="malicious"){
                    maliciousNum++;
                }else if(strCategory=="undetected"){
                    undetected++;
                }
                total=maliciousNum+undetected;
            }

        }
    }
    if(total>0){
        int per=maliciousNum*10000/total;
        ui->labWarning->setText(tr("文件风险：%1 %").arg(maliciousNum));
        ui->labResult->setText(tr("扫描结果：%1 个扫描引擎查出，共 %2 个。").arg(maliciousNum).arg(total));
    }else{
        ui->labWarning->setText(tr("该文件类型不受支持！"));
        ui->labResult->setText(tr("一分钟最多查询4次！且文件大小不能超过32MB！"));
    }
    // Qt::WindowFlags flags;
    // setWindowFlags(flags|Qt::WindowCloseButtonHint|Qt::WindowStaysOnTopHint);
    cleanUp();
}

void AnalyserResult::onAnalyseFailed()
{
    ui->labWarning->setText(tr("扫描发生错误！"));
    ui->labResult->setText(tr("一分钟最多查询4次！"));
    cleanUp();
}
