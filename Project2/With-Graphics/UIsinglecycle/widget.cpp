#include "widget.h"
#include "ui_widget.h"
#include "singlecycle.h"
#include<QTextEdit>
#include<QPushButton>
#include<QLabel>
#include<QDebug>
#include<QFileDialog>
#include<QMessageBox>
#include<iostream>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonLOAD_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("(*.png *.xpm *.jpg *.mc)"));


    // change the QString to string
    string ss = fileName.toUtf8().constData();

    // Add double //
    int n = ss.length();
    for(int i=0;i<n;i++){
        string add = "//";
        if(ss[i]=='/')
        {
            ss.replace(i,1,add);
            i+=2;
        }
    }
    char adrss[100] = {};

    n = ss.length();
    for(int i=0;i<n;i++)
        adrss[i] = ss[i];
    read_instruction(adrss);
    single_cycle();
}

int pc = 0;
int Register[16] = {0};
float Register_counter[16] = {0};
int UseOfMemory = 0;
extern int instruction_size;
void Widget::on_pushButtonNEXT_clicked()
{
    int control_signals[11] = {0};
    if(instruction_int[pc] == 234881024 || pc >= instruction_size)
    {
        Add1(&pc);
        QString pcqstr = QString::number(pc);
        QMessageBox::warning(this, "Message!", "Cycles Finished! Now You can see: "
                                               "\n Number Of Instructions, \n Number Of Use Of Memory,"
                                               "\n and The Usage Percentage Of Each Register.");
        //        QMessageBox::
        QString useofmemqstr = QString::number(UseOfMemory);
        ui->textNumberOfInstruction->setText(pcqstr);
        ui->textUseOfMemory->setText(useofmemqstr);
        //        QString cntreg[16];
        float sum = 0;
        for(int i = 0; i < 16; i++)
            sum += Register_counter[i];
        //        for(int i = 0; i < 16; i++)
        //        {
        //            cntreg[i] = QString::number(Register_counter[i]/sum *100);
        //        }

        ui->lcdNumber->display(Register_counter[0]/sum *100);
        ui->lcdNumber_2->display(Register_counter[1]/sum *100);
        ui->lcdNumber_3->display(Register_counter[2]/sum *100);
        ui->lcdNumber_4->display(Register_counter[3]/sum *100);
        ui->lcdNumber_5->display(Register_counter[4]/sum *100);
        ui->lcdNumber_6->display(Register_counter[5]/sum *100);
        ui->lcdNumber_7->display(Register_counter[6]/sum *100);
        ui->lcdNumber_8->display(Register_counter[7]/sum *100);
        ui->lcdNumber_9->display(Register_counter[8]/sum *100);
        ui->lcdNumber_10->display(Register_counter[9]/sum *100);
        ui->lcdNumber_11->display(Register_counter[10]/sum *100);
        ui->lcdNumber_12->display(Register_counter[11]/sum *100);
        ui->lcdNumber_13->display(Register_counter[12]/sum *100);
        ui->lcdNumber_14->display(Register_counter[13]/sum *100);
        ui->lcdNumber_15->display(Register_counter[14]/sum *100);
        ui->lcdNumber_16->display(Register_counter[15]/sum *100);
        //        ui->lcdNumber->display(Register_counter[0]);
        //        ui->lcdNumber_2->display(Register_counter[1]);
        //        ui->lcdNumber_3->display(Register_counter[2]);
        //        ui->lcdNumber_4->display(Register_counter[3]);
        //        ui->lcdNumber_5->display(Register_counter[4]);
        //        ui->lcdNumber_6->display(Register_counter[5]);
        //        ui->lcdNumber_7->display(Register_counter[6]);
        //        ui->lcdNumber_8->display(Register_counter[7]);
        //        ui->lcdNumber_9->display(Register_counter[8]);
        //        ui->lcdNumber_10->display(Register_counter[9]);
        //        ui->lcdNumber_11->display(Register_counter[10]);
        //        ui->lcdNumber_12->display(Register_counter[11]);
        //        ui->lcdNumber_13->display(Register_counter[12]);
        //        ui->lcdNumber_14->display(Register_counter[13]);
        //        ui->lcdNumber_15->display(Register_counter[14]);
        //        ui->lcdNumber_16->display(Register_counter[15]);
    }
    else
    {
        each_cycle(&pc, control_signals);

        QString regtext[16];
        for(int i = 0; i < 16; i++)
        {
            regtext[i] = QString::number(Register[i]);
        }

        ui->textReg1->setText(regtext[0]);
        ui->textReg2->setText(regtext[1]);
        ui->textReg3->setText(regtext[2]);
        ui->textReg4->setText(regtext[3]);
        ui->textReg5->setText(regtext[4]);
        ui->textReg6->setText(regtext[5]);
        ui->textReg7->setText(regtext[6]);
        ui->textReg8->setText(regtext[7]);
        ui->textReg9->setText(regtext[8]);
        ui->textReg10->setText(regtext[9]);
        ui->textReg11->setText(regtext[10]);
        ui->textReg12->setText(regtext[11]);
        ui->textReg13->setText(regtext[12]);
        ui->textReg14->setText(regtext[13]);
        ui->textReg15->setText(regtext[14]);
        ui->textReg16->setText(regtext[15]);
    }
}

void Widget::on_pushButtonHalt_clicked()
{
    ui->textReg1->setText(0);
    ui->textReg2->setText(0);
    ui->textReg3->setText(0);
    ui->textReg4->setText(0);
    ui->textReg5->setText(0);
    ui->textReg6->setText(0);
    ui->textReg7->setText(0);
    ui->textReg8->setText(0);
    ui->textReg9->setText(0);
    ui->textReg10->setText(0);
    ui->textReg11->setText(0);
    ui->textReg12->setText(0);
    ui->textReg13->setText(0);
    ui->textReg14->setText(0);
    ui->textReg15->setText(0);
    ui->textReg16->setText(0);
    ui->lcdNumber->display(0);
    ui->lcdNumber_2->display(0);
    ui->lcdNumber_3->display(0);
    ui->lcdNumber_4->display(0);
    ui->lcdNumber_5->display(0);
    ui->lcdNumber_6->display(0);
    ui->lcdNumber_7->display(0);
    ui->lcdNumber_8->display(0);
    ui->lcdNumber_9->display(0);
    ui->lcdNumber_10->display(0);
    ui->lcdNumber_11->display(0);
    ui->lcdNumber_12->display(0);
    ui->lcdNumber_13->display(0);
    ui->lcdNumber_14->display(0);
    ui->lcdNumber_15->display(0);
    ui->lcdNumber_16->display(0);
    ui->textNumberOfInstruction->setText("");
    ui->textUseOfMemory->setText("");
    pc = 0;
    for(int i = 0; i < 16; i++)
    {
        Register[i] = 0;
        Register_counter[i] = 0;
    }
    UseOfMemory = 0;
    instruction_size = 0;
}
