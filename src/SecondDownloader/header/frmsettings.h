#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QWidget>


namespace Ui {
class frmSettings;
}

class frmSettings : public QWidget
{
    Q_OBJECT

public:
    explicit frmSettings(QWidget *parent = nullptr);
    inline void refresh(){
        iniSettings();
    }
    ~frmSettings();
private slots:
    void on_chkRunHide_clicked(bool checked);

    void on_chkRunAuto_clicked(bool checked);

    void on_rdbThemeFollow_clicked(bool checked);

    void on_rdbThemeWhite_clicked(bool checked);

    void on_rdbThemeBlack_clicked(bool checked);

    void on_rdbLanDef_clicked(bool checked);

    void on_rdbLanZhSimplified_clicked(bool checked);

    void on_rdbLanZhTraditional_clicked(bool checked);

    void on_rdbLanEn_clicked(bool checked);

    void on_rdbManageAll_clicked(bool checked);

    void on_rdbManageNone_clicked(bool checked);

    void on_chkProtrolHttps_clicked(bool checked);

    void on_chkProtrolHttp_clicked(bool checked);

    void on_chkProtrolFtp_clicked(bool checked);

    void on_chkProtrolFtps_clicked(bool checked);

    void on_chkProtrolOthers_clicked(bool checked);

    void on_lineSaveLocation_textChanged(const QString &arg1);

    void on_chkDownLoadClip_clicked(bool checked);

    void on_chkFinishedScan_clicked(bool checked);

    void on_chkFinishedBell_clicked(bool checked);

    void oncomboFinishedBellcurrentTextChanged(const QString &arg1);

    void on_rdbFinishedDisplay_clicked(bool checked);

    void on_rdbFinishedOpenFile_clicked(bool checked);

    void on_rdbFinishedOpenFolder_clicked(bool checked);

    void on_rdbFinishedNotNotice_clicked(bool checked);

    void on_chkGithubProxy_clicked(bool checked);

    void on_btnSaveSelect_clicked();



private:
    Ui::frmSettings *ui;
    void iniSettings();
    QStringList getAllWavs(QString location);
    bool comboFinishBellInied=0;
};

#endif // FRMSETTINGS_H
