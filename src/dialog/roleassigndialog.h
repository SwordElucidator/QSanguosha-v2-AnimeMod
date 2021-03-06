#ifndef _ROLE_ASSIGN_DIALOG_H
#define _ROLE_ASSIGN_DIALOG_H


class RoleAssignDialog : public QDialog
{
    Q_OBJECT

public:
    RoleAssignDialog(QWidget *parent);
    static const int S_CORNER_SIZE = 5;

protected:
    virtual void accept();
    virtual void reject();

private:
    QListWidget *list;
    QComboBox *role_ComboBox;
    QMap<QString, QString> role_mapping;

private slots:
    void updateRole(int index);
    void updateRole(QListWidgetItem *current);
    void moveUp();
    void moveDown();
};

#endif

