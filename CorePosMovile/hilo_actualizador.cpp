#include "hilo_actualizador.h"
#include <QtCore/QDebug>



hilo_actualizador * hilo_actualizador::_instance = NULL;

hilo_actualizador::hilo_actualizador(QObject *parent) :
    QThread(parent)
{
    setUp();
}

void hilo_actualizador::setUp()
{
    qDebug() << "Set Up del hilo";
    //start( QThread::LowPriority) ;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pruebas");
    if(!db.open()){
        qDebug() << "ERRORth: " << db.lastError();
    }
    dowork();
}

void hilo_actualizador::dowork()
{
    //emit setservice("Dentro del hilo");
    QEventLoop loop;
    timer = new QTimer(this);
    timer->setInterval(120000); //cada 2 minutos
    connect(timer, SIGNAL(timeout()), this, SLOT(CicloRecover()));
    qDebug() << "Corriendo el hilo";
    timer->start();
    loop.exec();
    exit();
}

void hilo_actualizador::CicloRecover()
{
    double valorxquery=0;
    int contador=1;
    qDebug() << "CicloRecove Estado Recuperación";
    QTime myTimer;
    myTimer.start();
    QSqlQuery query(db);
    QSqlQuery query2(db);
    query.prepare("SELECT count(*) as valor FROM HistCatalogos where APLICADO=0 ORDER BY ai_ln ");

    if(!query.exec()){
      qDebug() << "ERRORth2: " << query.lastError().text();
      //return 0;
    }

    while(query.next()){
        qDebug() << "son : " << query.value("valor").toString()+" actualizaciones";
        if(query.value("valor").toInt()==0){
             valorxquery=1;
            break;
        }
        valorxquery=1/query.value("valor").toInt();

    }
    query.finish();
    query.prepare("SELECT * FROM HistCatalogos where APLICADO=0 ORDER BY ai_ln ");

    if(!query.exec()){
      qDebug() << "ERRORth2: " << query.lastError().text();
      //return 0;
    }
    while(query.next())
    {
       QString catAct=query.value("cat_act").toString();
       QString xml=query.value("xml").toString();
       int linea_actual=query.value("ai_ln").toInt();
       QString operacion="";
        QString queryy="";
       qDebug() << "RESULTADOS en hilo: " << linea_actual << " , "<< catAct ;
       if(catAct == "ABC_BrandW"){//mientras no se considere a las marcas
          emit setservice(valorxquery*contador);
           contador++;
           continue;
       }

       QDomDocument xmlt;
       QVariant xml1=xml;
       bool ejecutado=true;
       xmlt.setContent(xml1.toByteArray());
       if ( catAct == "ABC_ItemW")
       {
           operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();
           if(operacion=="A"){
             QString id_itm=xmlt.elementsByTagName("ID_ITM").at(0).toElement().text();
             QString id_itm_sl_prc= xmlt.elementsByTagName("ID_ITM_SL_PRC").at(0).toElement().text();
             QString id_mrhrc_gp=xmlt.elementsByTagName("ID_MRHRC_GP").at(0).toElement().text();
             QString id_brn=xmlt.elementsByTagName("ID_BRN").at(0).toElement().text();
             QString lu_exm_tx=xmlt.elementsByTagName("LU_EXM_TX").at(0).toElement().text();
             QString nm_itm=xmlt.elementsByTagName("NM_ITM").at(0).toElement().text();
             QString de_itm=xmlt.elementsByTagName("DE_ITM").at(0).toElement().text();
             QString ty_itm=xmlt.elementsByTagName("TY_ITM").at(0).toElement().text();
             QString food_stamp=xmlt.elementsByTagName("FOOD_STAMP_EX").at(0).toElement().text();
             QString id_spr=xmlt.elementsByTagName("ID_SPR").at(0).toElement().text();
             QString lu_uom=xmlt.elementsByTagName("LU_UOM").at(0).toElement().text();
             QString cp_un_dl_ls_rsv= xmlt.elementsByTagName("CP_UN_SL_LS_RSV").at(0).toElement().text();
             QString sell_price=xmlt.elementsByTagName("SELL_PRICE").at(0).toElement().text();
             QString price_list=xmlt.elementsByTagName("PRICE_LIST").at(0).toElement().text();
             QString ofer_price=xmlt.elementsByTagName("OFER_PRICE").at(0).toElement().text();
             QString fl_vl_price=xmlt.elementsByTagName("FL_VL_PRICE").at(0).toElement().text();
             QString id_itm_ps=xmlt.elementsByTagName("ID_ITM_PS").at(0).toElement().text();
             QString id_itm_ps_qfr= xmlt.elementsByTagName("ID_ITM_PS_QFR").at(0).toElement().text();
             QString id_strgrp=xmlt.elementsByTagName("ID_STRGRP").at(0).toElement().text();
             QString id_prep_cc=xmlt.elementsByTagName("ID_PREP_CC").at(0).toElement().text();
             QString qu_itm=xmlt.elementsByTagName("QU_ITM").at(0).toElement().text();
             QString picture=xmlt.elementsByTagName("PICTURE").at(0).toElement().text();
             if(picture.length()<1)
                 picture="null";


             QString queri=queryy= abc_item(id_itm,id_itm_sl_prc,id_mrhrc_gp,id_brn,lu_exm_tx,
                                            nm_itm,de_itm, ty_itm,food_stamp,id_spr,lu_uom
                                            ,cp_un_dl_ls_rsv ,id_itm_sl_prc ,sell_price,
                                            price_list,ofer_price,fl_vl_price,
                                            id_itm_ps,id_itm_ps_qfr,id_prep_cc,qu_itm);
             ejecutado = true;
           }
          // QDomNodeList XML = (histcatalogos.at(x).toElement()).elementsByTagName("XML");
       }
       else if(catAct == "ABC_disbursementfundsreceiptreasonW"){//ac
           operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();
           QString rcv=xmlt.elementsByTagName("ID_RCV_DSB").at(0).toElement().text();
           QString de= xmlt.elementsByTagName("DE_RCV").at(0).toElement().text();
           QString ty=xmlt.elementsByTagName("TV_RCV").at(0).toElement().text();

         if(operacion=="A"){

               QString queri=queryy= abc_disbursement_a(rcv,de,ty);

         }
         else if(operacion=="C"){
             QString queri=queryy=abc_disbursement_c(rcv,de,ty);

         }
       }
       else if(catAct == "ABC_MerchandiseHierarchyGroupW"){//ac
           operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();
           QString gp=xmlt.elementsByTagName("ID_MRHRC_GP").at(0).toElement().text();
           QString prnt= xmlt.elementsByTagName("ID_MRHC_PRNT").at(0).toElement().text();
           QString nm=xmlt.elementsByTagName("NM_MRHRC_GP").at(0).toElement().text();
           QString pe=xmlt.elementsByTagName("PE_PROFIT").at(0).toElement().text();
           QString tx=xmlt.elementsByTagName("ID_GP_TX").at(0).toElement().text();
           QString food=xmlt.elementsByTagName("FOOD_STAMP_EX").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_merchandisegroup_a(gp,prnt,nm,pe,tx,food);

               qDebug() << "syncpos.cpp queri 2 " << queri;
           }
           else if(operacion=="C"){
                   QString queri=queryy=abc_merchandisegroup_c(gp,prnt,nm,pe,tx,food);
                   //ejecutado = sqlQuery.exec( queri ) ;
           }
       }
       else if(catAct == "OperatorW"|| catAct == "ABC_OperatorW"){//ac
           operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

           QString OPR= xmlt.elementsByTagName("ID_OPR").at(0).toElement().text();
           QString STR=xmlt.elementsByTagName("ID_OPR").at(0).toElement().text();
           QString NM=xmlt.elementsByTagName("NM_OPR").at(0).toElement().text();
           QString PWD=xmlt.elementsByTagName("PWD_ACS_OPR").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_operator_a(OPR,STR,NM,PWD);

           }
           else if(operacion=="C"){
               QString queri=queryy=abc_operator_c(OPR,STR,NM,PWD);

           }
       }
       else if(catAct == "OperatorGroupW"||catAct == "ABC_OperatorGroupW"){//ac
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString STR= xmlt.elementsByTagName("ID_STR_RT").at(0).toElement().text();
                   QString GP=xmlt.elementsByTagName("ID_GP_WRK").at(0).toElement().text();
                   QString OPR=xmlt.elementsByTagName("ID_OPR").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_operatorgroup_a(STR,GP,OPR);

           }
           else if(operacion=="C"){
               QString queri=queryy=abc_operatorgroup_c(STR,GP,OPR);

           }
       }
       else if(catAct == "ABC_POSIdentityW"){//abc
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString ITM_PS= xmlt.elementsByTagName("ID_ITM_PS").at(0).toElement().text();
                   QString QFR=xmlt.elementsByTagName("ID_ITM_PS_QFR").at(0).toElement().text();
                   QString ID_SL_PRC=xmlt.elementsByTagName("ID_ITM_SL_PRC").at(0).toElement().text();
                   QString IDT=xmlt.elementsByTagName("ID_ITM").at(0).toElement().text();
                   QString PREP_CC= xmlt.elementsByTagName("ID_PREP_CC").at(0).toElement().text();
                   QString QU=xmlt.elementsByTagName("QU_ITM").at(0).toElement().text();
                   QString SELL=xmlt.elementsByTagName("SELL_PRICE").at(0).toElement().text();
                   QString LIST=xmlt.elementsByTagName("PRICE_LIST").at(0).toElement().text();
                   QString OFER= xmlt.elementsByTagName("OFER_PRICE").at(0).toElement().text();
                   QString FL_VL=xmlt.elementsByTagName("FL_VL_PRICE").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_posidentity_a(ITM_PS,QFR,ID_SL_PRC,IDT,PREP_CC,QU,SELL,LIST,OFER,FL_VL);

           }
           //else if(operacion=="C"){
           //    QString queri=queryy=abc_posidentity_c(ITM_PS,QFR,ID_SL_PRC,IDT,PREP_CC,QU,SELL,LIST,OFER,FL_VL);

           //}
           else if(operacion=="B"){
               QString queri=queryy=abc_posidentity_b(ID_SL_PRC,ITM_PS,QFR);

           }
       }
       else if(catAct == "ABC_SupplierW"){//ac
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString SPR= xmlt.elementsByTagName("ID_SPR").at(0).toElement().text();
                   QString PRTY=xmlt.elementsByTagName("ID_PRTY").at(0).toElement().text();
                   QString TY=xmlt.elementsByTagName("TY_RO_PRTY").at(0).toElement().text();
                   QString NM=xmlt.elementsByTagName("NM_SPR").at(0).toElement().text();
                   QString MF=xmlt.elementsByTagName("FL_MF_SPR_IS").at(0).toElement().text();
                   QString PERI=xmlt.elementsByTagName("PERIODICITY").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_suplier_a(SPR,PRTY,TY,NM,MF,PERI);

           }
           else if(operacion=="C"){
               QString queri=queryy=abc_suplier_c(SPR,PRTY,TY,NM,MF,PERI);


           }
       }
       else if(catAct == "ABC_TaxableGroupW"){//ac
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString IDG= xmlt.elementsByTagName("ID_GP_TX").at(0).toElement().text();
                   QString NMG=xmlt.elementsByTagName("NM_GP_TX").at(0).toElement().text();
                   QString RCPT=xmlt.elementsByTagName("CD_RCPT_PRN").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_taxablegroup_a(IDG,NMG,RCPT);

           }
           else if(operacion=="C"){
               QString queri=queryy=abc_taxablegroup_c(IDG,NMG,RCPT);

           }
       }
       else if(catAct == "ABC_TaxGroupRuleW"){//ac
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString ATHY= xmlt.elementsByTagName("ID_ATHY_TX").at(0).toElement().text();
                   QString GP=xmlt.elementsByTagName("ID_GP_TX").at(0).toElement().text();
                   QString AI=xmlt.elementsByTagName("AI_CMPND").at(0).toElement().text();
                   QString NM=xmlt.elementsByTagName("NM_RU_TX").at(0).toElement().text();
                   QString ACNT=xmlt.elementsByTagName("ID_ACNT_LDG").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_taxgrouprule_a(ATHY,GP,AI,NM,ACNT);


           }
           else if(operacion=="C"){
               QString queri=queryy=abc_taxgrouprule_c(ATHY,GP,AI,NM,ACNT);

           }
       }
       else if(catAct == "ABC_TaxRateRuleW"){//AC
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString athy= xmlt.elementsByTagName("AD_THY_TX").at(0).toElement().text();
                   QString gp=xmlt.elementsByTagName("ID_GP_TX").at(0).toElement().text();
                   QString ai=xmlt.elementsByTagName("AI_TX_RT_RU").at(0).toElement().text();
                   QString ty=xmlt.elementsByTagName("TY_TX_RT_RU").at(0).toElement().text();
                   QString txbm= xmlt.elementsByTagName("MO_TXBM_MNM").at(0).toElement().text();
                   QString txbl= xmlt.elementsByTagName("MO_TXBL_MXM").at(0).toElement().text();
                   QString mo=xmlt.elementsByTagName("MO_RT_TX").at(0).toElement().text();
                   QString pe=xmlt.elementsByTagName("PE_RT_TX").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_taxraterule_a(athy,gp,ai,ty,txbm,txbl,mo,pe);
                           qDebug() << "query de prueba " <<queri;


           }
           else if(operacion=="C"){
               QString queri=queryy=abc_taxraterule_c(athy,gp,ai,ty,txbm,txbl,mo,pe);
                           qDebug() << "query de prueba " <<queri;


           }
       }
       else if(catAct == "ABC_TenderW"){//ac
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString ty= xmlt.elementsByTagName("TY_TND").at(0).toElement().text();
                   QString act=xmlt.elementsByTagName("ID_ACT_LDG").at(0).toElement().text();
                   QString cny=xmlt.elementsByTagName("ID_CNY").at(0).toElement().text();
                   QString tnd=xmlt.elementsByTagName("DE_TND").at(0).toElement().text();
                   QString nmb_srz= xmlt.elementsByTagName("FL_NMB_SRZ").at(0).toElement().text();
                   QString azn_rq=xmlt.elementsByTagName("FL_AZN_RQ").at(0).toElement().text();
                   QString mth_azn=xmlt.elementsByTagName("LU_MTH_AZN").at(0).toElement().text();
                   QString ep_rq=xmlt.elementsByTagName("FL_DT_AZN_EP_RQ").at(0).toElement().text();
                   QString mxm_alow= xmlt.elementsByTagName("IN_WIT_AZN_MXM_ALOW").at(0).toElement().text();
                   QString rq_ct=xmlt.elementsByTagName("FL_IDTN_RQ_CT").at(0).toElement().text();
                   QString prsl_rq=xmlt.elementsByTagName("FL_ID_PRSL_RQ").at(0).toElement().text();
                   QString lcl_cny=xmlt.elementsByTagName("FL_AVLB_LCL_CNY").at(0).toElement().text();
                   QString ct_rq=xmlt.elementsByTagName("FL_SGNTR_CT_RQ").at(0).toElement().text();
                   QString tnd_chn=xmlt.elementsByTagName("MO_TH_TND_CHN").at(0).toElement().text();
                   QString drw_open= xmlt.elementsByTagName("FL_DRW_OPEN").at(0).toElement().text();
                   QString tndce_off=xmlt.elementsByTagName("MO_APVL_TNDCE_OFF").at(0).toElement().text();
                   QString endsm_rq=xmlt.elementsByTagName("FL_ENDSM_RQ").at(0).toElement().text();
                   QString plaz=xmlt.elementsByTagName("PLAZOS").at(0).toElement().text();
                   QString itm_ps= xmlt.elementsByTagName("ID_ITM").at(0).toElement().text();
                   QString btn=xmlt.elementsByTagName("BTN_ASIGNED").at(0).toElement().text();
                   QString food=xmlt.elementsByTagName("FOOD_STAMP_EX").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_tender_a(ty,act,cny,tnd,nmb_srz,azn_rq,mth_azn,ep_rq,mxm_alow,rq_ct,prsl_rq,lcl_cny,ct_rq,tnd_chn,drw_open,tndce_off,endsm_rq,plaz,itm_ps,btn,food);
                           qDebug() << "query de prueba " <<queri;


           }
           else if(operacion=="C"){
               QString queri=queryy=abc_tender_c(ty,act,cny,tnd,nmb_srz,azn_rq,mth_azn,ep_rq,mxm_alow,rq_ct,prsl_rq,lcl_cny,ct_rq,tnd_chn,drw_open,tndce_off,endsm_rq,plaz,itm_ps,btn,food);
                           qDebug() << "query de prueba " <<queri;


           }
       }
       else if(catAct == "TillW"||catAct == "ABC_TillW"){//ac
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString str= xmlt.elementsByTagName("ID_STR_RT").at(0).toElement().text();
                   QString rpsty=xmlt.elementsByTagName("ID_RPSTY").at(0).toElement().text();
                   QString ws=xmlt.elementsByTagName("ID_WS").at(0).toElement().text();
                   QString opr=xmlt.elementsByTagName("ID_OPR").at(0).toElement().text();
                   QString sc=xmlt.elementsByTagName("CP_BLNC_DFLT_OPN").at(0).toElement().text();
                   QString opn=xmlt.elementsByTagName("CP_BLNC_DFLT_OPN").at(0).toElement().text();
                   QString mxm=xmlt.elementsByTagName("LU_TND_MXM_ALW").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_till_a(str,rpsty,ws,opr,sc,opn,mxm);
                           qDebug() << "query de prueba " <<queri;


           }
           else if(operacion=="C"){
               QString queri=queryy=abc_till_c(str,rpsty,ws,opr,sc,opn,mxm);
                           qDebug() << "query de prueba " <<queri;


           }
       }
       else if(catAct == "ABC_buttonconfigW"){//abc
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString id_str= xmlt.elementsByTagName("ID_STR_RT").at(0).toElement().text();
                   QString btnset=xmlt.elementsByTagName("ID_BTNSET").at(0).toElement().text();
                   QString btn=xmlt.elementsByTagName("ID_BTN").at(0).toElement().text();
                   QString prnt=xmlt.elementsByTagName("ID_BTN_PRNT").at(0).toElement().text();
                   QString ty= xmlt.elementsByTagName("TY_BTN").at(0).toElement().text();
                   QString wt=xmlt.elementsByTagName("BTN_WT").at(0).toElement().text();
                   QString nm=xmlt.elementsByTagName("NM_BTN").at(0).toElement().text();
                   QString de=xmlt.elementsByTagName("DE_BTN").at(0).toElement().text();
                   QString itm= xmlt.elementsByTagName("ID_ITM").at(0).toElement().text();
                   QString icon=xmlt.elementsByTagName("ICON_ADDRESS").at(0).toElement().text();
                   QString strgrp=xmlt.elementsByTagName("ID_STRGRP").at(0).toElement().text();
                   QString itm_ps=xmlt.elementsByTagName("ID_ITM_PS").at(0).toElement().text();
                   QString qfr=xmlt.elementsByTagName("ID_ITM_PS_QFR").at(0).toElement().text();
                   QString webserv=xmlt.elementsByTagName("WEBSERV_NAME").at(0).toElement().text();
                   QString param= xmlt.elementsByTagName("PARAMS_LIST").at(0).toElement().text();
                   QString pos=xmlt.elementsByTagName("POSITION").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_buttonconfig_a(id_str,btnset,btn,prnt,ty,wt,nm,de,itm,strgrp,itm_ps,qfr,webserv,param,pos,"");//resivar parametros
                           qDebug() << "query de prueba " <<queri;


           }
           else if(operacion=="C"){}
           else if(operacion=="B"){}
       }
       else if(catAct == "ABC_POSIdentityW"){//abc
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString ITM_PS= xmlt.elementsByTagName("ID_ITM_PS").at(0).toElement().text();
                   QString QFR=xmlt.elementsByTagName("ID_ITM_PS_QFR").at(0).toElement().text();
                   QString ID_SL_PRC=xmlt.elementsByTagName("ID_ITM_SL_PRC").at(0).toElement().text();
                   QString IDT=xmlt.elementsByTagName("ID_ITM").at(0).toElement().text();
                   QString PREP_CC= xmlt.elementsByTagName("ID_PREP_CC").at(0).toElement().text();
                   QString QU=xmlt.elementsByTagName("QU_ITM").at(0).toElement().text();
                   QString SELL=xmlt.elementsByTagName("SELL_PRICE").at(0).toElement().text();
                   QString LIST=xmlt.elementsByTagName("PRICE_LIST").at(0).toElement().text();
                   QString OFER= xmlt.elementsByTagName("OFER_PRICE").at(0).toElement().text();
                   QString FL_VL=xmlt.elementsByTagName("FL_VL_PRICE").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_posidentity_a(ITM_PS,QFR,ID_SL_PRC,IDT,PREP_CC,QU,SELL,LIST,OFER,FL_VL);

           }
           //else if(operacion=="C"){
           //    QString queri=queryy=abc_posidentity_c(ITM_PS,QFR,ID_SL_PRC,IDT,PREP_CC,QU,SELL,LIST,OFER,FL_VL);

           //}
           else if(operacion=="B"){
               QString queri=queryy=abc_posidentity_b(ID_SL_PRC,ITM_PS,QFR);

           }
       }
       else if(catAct == "ABC_RetailStoreW"){//abc ABC_WorkstationW
                   operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

                   QString id_str= xmlt.elementsByTagName("ID_STR_RT").at(0).toElement().text();
                   QString prty=xmlt.elementsByTagName("ID_PRTY").at(0).toElement().text();
                   QString ty=xmlt.elementsByTagName("TY_RO_PRTY").at(0).toElement().text();
                   QString str=xmlt.elementsByTagName("ID_STRGRP").at(0).toElement().text();
                   QString nm= xmlt.elementsByTagName("NM_STR_RT").at(0).toElement().text();
                   QString enc1=xmlt.elementsByTagName("ENC_PRN1").at(0).toElement().text();
                   QString enc2=xmlt.elementsByTagName("ENC_PRN2").at(0).toElement().text();
                   QString pie1=xmlt.elementsByTagName("PIE_PRN1").at(0).toElement().text();
                   QString pie2= xmlt.elementsByTagName("PIE_PRN2").at(0).toElement().text();
                   QString merch=xmlt.elementsByTagName("ID_MERCHANT_ED").at(0).toElement().text();
                   QString p1=xmlt.elementsByTagName("POSITION1").at(0).toElement().text();
                   QString p2=xmlt.elementsByTagName("POSITION2").at(0).toElement().text();
                   QString p3=xmlt.elementsByTagName("POSITION3").at(0).toElement().text();
                   QString p4=xmlt.elementsByTagName("POSITION4").at(0).toElement().text();
                   QString p5= xmlt.elementsByTagName("POSITION5").at(0).toElement().text();
                   QString p6=xmlt.elementsByTagName("POSITION16").at(0).toElement().text();

           if(operacion=="A"){
               QString queri=queryy=abc_retailstore_a(id_str,prty,ty,str,nm,enc1,enc2,pie1,pie2,merch,p1,p2,p3,p4,p5,p6);
                           qDebug() << "query de prueba " <<queri;


           }
           else if(operacion=="C"){}
           else if(operacion=="B"){}
       }
       else if(catAct == "ABC_WorkstationW"){//abc ABC_WorkstationW
           operacion=xmlt.elementsByTagName("Operacion").at(0).toElement().text();

           QString id_str= xmlt.elementsByTagName("ID_STR_RT").at(0).toElement().text();
           QString WS=xmlt.elementsByTagName("ID_WS").at(0).toElement().text();
           QString EQ=xmlt.elementsByTagName("ID_EQ").at(0).toElement().text();
           QString SERIE=xmlt.elementsByTagName("SERIE").at(0).toElement().text();
           QString QU= xmlt.elementsByTagName("QU_TL_WS").at(0).toElement().text();
           QString FL=xmlt.elementsByTagName("FL_MOD_TRG").at(0).toElement().text();


               if(operacion=="A"){
                   QString queri=queryy=abc_workstation_a(id_str,WS,EQ,SERIE,QU,FL);

               }
               else if(operacion=="C"){}
               else if(operacion=="B"){}
               }
       if(queryy.compare("ok")==0){
           qDebug() << " correto " <<queryy ;
           query.prepare("update HistCatalogos set aplicado=1 where "+query.value("ai_ln").toString());

           if(!query.exec()){
             qDebug() << "ERRORth4: " << query.lastError().text();
             //return 0;
           }
           //emit setservice(valorxquery*contador);
            contador++;
       }
      else{
        qDebug() <<"Error en la actualizazcio" << catAct;
       }
       ///fin de las actualizaciones
     qDebug()<<"transcurridos: "<<myTimer.elapsed() <<" milisegundos";
    }
}

hilo_actualizador * hilo_actualizador::instance( QObject * o)
{
    if ( _instance == NULL )
    {
        _instance = new hilo_actualizador( o ) ;
    }
    return _instance ;

}


//CORRECTA
QString hilo_actualizador::abc_item(QString idt, QString sl_prc, QString merch, QString brand, QString exm_tx,
                  QString nombre, QString descripcion, QString ty, QString food,
                  QString spr,QString lu_cnt,QString cp_un_sl,
                  QString id_sl_prc,QString sell,QString list,QString ofer,QString fl_vl, QString itm_ps,
                  QString qfr,QString prep_cc,QString qu){//pic null

    if(prep_cc.length()<=0){
        prep_cc="null";
    }
    if(exm_tx.length()<=0){
        exm_tx="null";
    }

    if(fl_vl.length()<=0||fl_vl.compare("NULL")==0){
        fl_vl="";
    }

    QString query="insert into itemsellprice(id_itm_sl_prc,sell_price,price_list,ofer_price,fl_vl_price) values("+id_sl_prc+","+sell+","+list+","+ofer+",'"+fl_vl+"');"+
            "insert into item(id_itm,id_itm_sl_prc,id_mrhrc_gp,id_brn,lu_exm_tx,nm_itm,de_itm,ty_itm,food_stamp_ex) values("+idt+","+id_sl_prc+","+merch+","+brand+","+exm_tx+",'"+nombre+"','"+descripcion+"','"+ty+"','"+food+"');"+
            "insert into stockitem (id_itm,id_spr,lu_cnt_sls_wt_un,cp_un_sl_ls_rsv) values("+idt+","+spr+",'"+lu_cnt+"',"+cp_un_sl+");"+
            "insert into posidentity(id_itm_ps,id_itm_ps_qfr,id_itm_sl_prc,id_itm,id_prep_cc,qu_itm,activo) values('"+itm_ps+"',"+qfr+","+id_sl_prc+","+idt+","+prep_cc+","+qu+",'S');"+
            "insert into itempictures(id_itm,picture) values ("+idt+", null);";
    qDebug()<< " query "+query;
   return ejecutaQuery(query);

}

//CORRECTA, REVISION DE NULOS PENDIENTE
QString hilo_actualizador::abc_disbursement_a(QString rcv,QString de,QString ty){
    QString query="insert into disbursementfundreceiptreason (id_rcv_dsb,de_rcv_dsb,ty_rcv) values ("+rcv+",'"+de+"','"+ty+"')";

    return ejecutaQuery(query);
}

//CORRECTA, REVISION DE NULOS PENDIENTE
QString hilo_actualizador::abc_disbursement_c(QString rcv,QString de,QString ty){
    QString query="update disbursementfundreceiptreason set id_rcv_dsb="+rcv+",de_rcv_dsb='"+de+"',ty_rcv='"+ty+"' where id_rcv_dsb="+rcv;
    return ejecutaQuery(query);
}

//CORRECTA
QString hilo_actualizador::abc_merchandisegroup_a(QString gp,QString prnt,QString nm,QString pe,QString tx,QString food){
    QString query="insert into merchandisehierarchygroup (id_mrhrc_gp,id_mrhc_prnt,nm_mrhrc_gp,pe_profit,id_gp_tx,food_stamp_ex) values ("+gp+","+prnt+",'"+nm+"',"+pe+","+tx+",'"+food+"')";
    return ejecutaQuery(query);
}

//CORRECTA
QString hilo_actualizador::abc_merchandisegroup_c(QString gp,QString prnt,QString nm,QString pe,QString tx,QString food){
    QString query="update merchandisehierarchygroup set id_mrhrc_gp="+gp+",id_mrhc_prnt="+prnt+",nm_mrhrc_gp='"+nm+"',pe_profit="+pe+",id_gp_tx="+tx+",food_stamp_ex='"+food+"' "+
    " where id_mrhrc_gp="+gp;
    return ejecutaQuery(query);
}
//correcta
QString hilo_actualizador::abc_operator_a(QString opr,QString str,QString nm,QString pwd){
    QString query="insert into operator (id_str_rt,id_opr,nm_opr,pwd_acs_opr) values ("+str+","+opr+",'"+nm+"','"+pwd+"');";
    return ejecutaQuery(query);
}
//correcta
QString hilo_actualizador::abc_operator_c(QString opr,QString str,QString nm,QString pwd){
    QString query="update operator set id_str_rt="+str+",id_opr="+opr+",nm_opr='"+nm+"',pwd_acs_opr ='"+pwd+"'"+
    " where id_opr="+opr+" and id_str_rt="+str+";";
    return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_operatorgroup_a(QString str,QString gp,QString opr){
    QString query="insert into operatorgroup (id_str_rt,id_gp_wrk,id_opr) values ("+str+","+gp+","+opr+");";
    return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_operatorgroup_c(QString str,QString gp,QString opr){
    QString query="update operatorgroup set id_str_rt="+str+",id_gp_wrk="+gp+",id_opr="+opr+
    "  where id_str_rt="+str+" and id_gp_wrk="+gp+" and id_opr="+opr+";";
    return ejecutaQuery(query);
}
//correcto revision de nulos pendiente
QString hilo_actualizador::abc_posidentity_a(QString itm_ps,QString qfr,QString id_sl_prc,QString idt,QString prep_cc,
                          QString qu,QString sell,QString list, QString ofer,QString fl_vl){
    if(prep_cc.length()<=0){
        prep_cc="null";
    }

    if(fl_vl.length()<=0||fl_vl.compare("NULL")==0){
        fl_vl="";
    }
    QString query="insert into itemsellprice(id_itm_sl_prc,sell_price,price_list,ofer_price,fl_vl_price) values("+id_sl_prc+","+sell+","+list+","+ofer+",'"+fl_vl+"');insert into posidentity(id_itm_ps,id_itm_ps_qfr,id_itm_sl_prc,id_itm,id_prep_cc,qu_itm,activo) values('"+itm_ps+"',"+qfr+","+id_sl_prc+","+idt+","+prep_cc+","+qu+",'S');";

    return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_posidentity_b(QString id_sl_prc,QString itm_ps,QString qfr){
    QString query="delete from itemsellprice where id_itm_sl_prc="+id_sl_prc+";"+
    "delete from posidentity where id_itm_ps='"+itm_ps+"' and id_itm_ps_qfr="+qfr+";";

    return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_retailstore_a(QString id_str,QString prty,QString ty_ro,QString strgrp,QString nm,
                          QString enc1,QString enc2,QString pie1,QString pie2,
                          QString id_merchant,QString p1,QString p2,QString p3,QString p4,
                          QString p5,QString p6){
    QString query="insert into retailstore(id_str_rt,id_prty,ty_ro_prty,id_strgrp,nm_str_rt,enc_prn1, enc_prn2,pie_prn1,pie_prn2, id_merchant_ed, position1, position2, position3, position4, position5, position6) values ("+id_str+","+prty+",'"+ty_ro+"',"+strgrp+",'"+nm+"','"+enc1+"','"+enc2+"','"+pie1+"','"+pie2+"',"+id_merchant+",'"+p1+"','"+p2+"','"+p3+"','"+p4+"','"+p5+"','"+p6+"');";

return ejecutaQuery(query);
}

//correcto
QString hilo_actualizador::abc_suplier_a(QString spr,QString prty,QString ty,QString nm,QString mf,QString peri){
    QString query="insert into supplier (id_spr,id_prty,ty_ro_prty,nm_spr,fl_mf_spr_is,periodicity) values ("+spr+","+prty+",'"+ty+"','"+nm+"','"+mf+"',"+peri+");";
return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_suplier_c(QString spr,QString prty,QString ty,QString nm,QString mf,QString peri){
    QString query="update supplier set id_spr="+spr+",id_prty="+prty+",ty_ro_prty='"+ty+"'"+
            ",nm_spr='"+nm+"',fl_mf_spr_is='"+mf+"',periodicity= "+peri+
    " where id_spr=spr;";
return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_taxablegroup_a(QString idg,QString nm,QString cd){
    QString query="insert into taxablegroup (id_gp_tx,nm_gp_tx,cd_rcpt_prn) values ("+idg+",'"+nm+"','"+cd+"');";
return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_taxablegroup_c(QString idg,QString nm,QString cd){
    QString query="update taxablegroup set id_gp_tx="+idg+",nm_gp_tx='"+nm+"',cd_rcpt_prn='"+cd+"'"+
    "where id_gp_tx="+idg+";";
return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_taxgrouprule_a(QString athy,QString gp, QString ai, QString nm, QString acnt){
    QString query="insert into taxgrouprule (id_athy_tx,id_gp_tx,ai_cmpnd,nm_ru_tx,id_acnt_ldg) values ("+athy+","+gp+","+ai+",'"+nm+"',"+acnt+");";
    return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_taxgrouprule_c(QString athy,QString gp, QString ai, QString nm,QString acnt){
    QString query ="update taxgrouprule set id_athy_tx="+athy+",id_gp_tx="+gp+",ai_cmpnd="+ai+","+
                   "nm_ru_tx='"+nm+"',id_acnt_ldg="+acnt+" where id_athy_tx="+athy+" and id_gp_tx="+gp+";";
    return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_taxraterule_a(QString athy,QString gp, QString ai, QString ty, QString txbm,QString txbl,QString mo,QString pe){
    QString query="insert into taxraterule (id_athy_tx,id_gp_tx,ai_tx_rt_ru,ty_tx_rt_ru,mo_txbm_mnm,mo_txbl_mxm,mo_rt_tx,pe_rt_tx) values ("+athy+","+gp+","+ai+",'"+ty+"',"+txbm+","+txbl+","+mo+","+pe+");";
    return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_taxraterule_c(QString athy,QString gp,QString ai, QString ty,QString txbm,QString txbl,QString mo,QString pe){
   QString query=" update taxraterule set id_athy_tx="+athy+",id_gp_tx="+gp+",ai_tx_rt_ru="+ai+","+
            "ty_tx_rt_ru='"+ty+"',mo_txbm_mnm="+txbm+",mo_txbl_mxm="+txbl+",mo_rt_tx="+mo+",pe_rt_tx="+pe+
    +"where id_athy_tx="+athy+" and id_gp_tx="+gp+" and ai_tx_rt_ru="+ai+";";
    return ejecutaQuery(query);
}

//correcto, revisar nulos pendiente
QString hilo_actualizador::abc_tender_a(QString ty,QString act,QString cny,QString tnd,QString nmb_srz,QString azn_rq,QString mth_azn,QString ep_rq,QString mxm_alow,QString rq_ct,QString prsl_rq,
                     QString lcl_cny,QString ct_rq,QString tnd_chn,QString drw_open,QString tndce_off,QString endsm_rq,QString plaz,QString itm_ps,QString btn,QString food
                     ){
    QString query="insert into tender (ty_tnd,id_act_ldg,id_cny,de_tnd,fl_nmb_srz,fl_azn_rq,lu_mth_azn,fl_dt_azn_ep_rq,in_wit_azn_mxm_alow,fl_idtn_rq_ct,fl_id_prsl_rq,fl_avlb_lcl_cny,fl_sgntr_ct_rq,mo_th_tnd_chn,fl_drw_open,mo_apvl_tndce_off,fl_endsm_rq,plazos,btn_asigned,food_stamp_ex) values ('"+ty+"',"+act+","+cny+",'"+tnd+"',"+nmb_srz+","+azn_rq+",'"+mth_azn+"','"+ep_rq+"',"+mxm_alow+","+rq_ct+","+prsl_rq+","+lcl_cny+","+ct_rq+","+tnd_chn+","+drw_open+","+tndce_off+","+endsm_rq+",'"+plaz+"','"+btn+"','"+food+"' );";
return ejecutaQuery(query);
}
//correcto, revisar nulos pendiente
QString hilo_actualizador::abc_tender_c(QString ty,QString act,QString cny,QString tnd,QString nmb_srz,QString azn_rq,
                     QString mth_azn,QString ep_rq,QString mxm_alow,QString rq_ct,QString prsl_rq,
                     QString lcl_cny,QString ct_rq,QString  tnd_chn,QString drw_open,QString  tndce_off,
                     QString endsm_rq,QString plaz,QString itm_ps,QString btn,QString food
                     ){
    QString query="update tender set ty_tnd='"+ty+"',id_act_ldg="+act+",id_cny="+cny+",de_tnd='"+tnd+"',fl_nmb_srz="+nmb_srz+","+
            "fl_azn_rq="+azn_rq+",lu_mth_azn='"+mth_azn+"',fl_dt_azn_ep_rq='"+ep_rq+"',in_wit_azn_mxm_alow="+mxm_alow+","+
            "fl_idtn_rq_ct="+rq_ct+",fl_id_prsl_rq="+prsl_rq+",fl_avlb_lcl_cny="+lcl_cny+",fl_sgntr_ct_rq="+ct_rq+","+
            "mo_th_tnd_chn="+tnd_chn+",fl_drw_open="+drw_open+",mo_apvl_tndce_off="+tndce_off+",fl_endsm_rq="+endsm_rq+",plazos='"+plaz+"',"+
            "btn_asigned='"+btn+"',food_stamp_ex='"+food+"' "+
    "where ty_tnd="+ty+";";
    return ejecutaQuery(query);
}

//correcto, revisar nulos pendiente
QString hilo_actualizador::abc_till_a(QString str,QString rpsty,QString ws,QString opr,QString sc,QString  opn, QString  mxm){
    if(opr.length()<=0){
        opr="null";
    }
    QString query="insert into till (id_str_rt,id_rpsty_tnd,id_ws,id_opr,cp_blnc_dflt_opn,lu_tnd_mxm_alw) values ("+str+","+rpsty+","+ws+","+opr+","+opn+","+mxm+");";
    return ejecutaQuery(query);
}

//correcto, revisar nulos pendiente
QString hilo_actualizador::abc_till_c(QString str,QString rpsty,QString ws,QString opr,QString sc,QString  opn, QString  mxm){
    if(opr.length()<=0){
        opr="null";
    }
    QString query="update till set id_str_rt="+str+",id_rpsty_tnd="+rpsty+",id_ws="+ws+",id_opr="+opr+","+
            "cp_blnc_dflt_opn="+opn+",lu_tnd_mxm_alw="+mxm+
     " where id_str_rt=str and id_rpsty_tnd=rpsty and id_ws=ws;";
return ejecutaQuery(query);
}
//correcto
QString hilo_actualizador::abc_workstation_a(QString str,QString ws,QString eq, QString se, QString  qu,QString fl){
    if(eq.length()<=0){
        eq="null";
    }
    QString query="insert into workstation (id_str_rt,id_ws,id_eq,serie,qu_tl_ws,fl_mod_trg)"
    "values ("+str+","+ws+","+eq+",'"+se+"',"+qu+","+fl+");";
return ejecutaQuery(query);
}

//correcto, revision de nulos pendiente
QString hilo_actualizador::abc_buttonconfig_a(QString id_str,QString btnset,QString btn,QString prnt,QString ty,QString wt,
                       QString nm, QString de,QString itm, QString icon,QString strgrp,
                       QString itm_ps,QString qfr,QString webserv,QString params,QString pos){

    QString query="insert into buttonconfig (id_str_rt,id_btnset,id_btn,id_btn_prnt,ty_btn,btn_wt,nm_btn,de_btn,id_itm,icon_address,id_strgrp,id_itm_ps,id_itm_ps_qfr,webserv_name,params_list,position) values ("+id_str+","+btnset+","+btn+","+prnt+",'"+ty+"',"+wt+",'"+nm+"','"+de+"',"+itm+",'"+icon+"',"+strgrp+",'"+itm_ps+"',"+qfr+",'"+webserv+"','"+params+"',"+pos+");";

return ejecutaQuery(query);
}
//correcto, revision de nulos pendiete
QString hilo_actualizador::buttonconfig_c(QString id_str,QString btnset,QString btn,QString prnt,QString ty,QString wt,
                       QString nm, QString de,QString itm, QString icon,QString strgrp,
                       QString itm_ps,QString qfr,QString webserv,QString param,QString pos){
    //update buttonconfig set (id_str_rt,id_btnset,id_btn,id_btn_prnt,ty_btn,btn_wt,nm_btn,de_btn,id_itm,icon_address,id_strgrp,id_itm_ps,id_itm_ps_qfr,webserv_name,params_list,position)
    //= (id_str,btnset,btn,prnt,ty,wt,nm,de,itm,icon,strgrp,itm_ps,qfr,webserv,param,pos)
    //where id_str_rt=id_str and id_btnset=btnset and id_btn=btn;

    return "ejecutaQuery(query)";
}

QString hilo_actualizador::buttonconfig_b(QString str,QString btnset,QString btn){
    //delete from buttonconfig where id_str_rt=str and id_btnset=btnset and id_btn=btn;
return "";
 }

QString hilo_actualizador::ejecutaQuery(QString quer){
   QSqlQuery query(db);
   //separados por ; cada insert
    QString resultado="ok";
   QStringList scriptQueries = quer.split(";");
   foreach (QString queryTxt, scriptQueries)
       {
           if (queryTxt.trimmed().isEmpty()) {
               continue;
           }
           if (!query.exec(queryTxt))
           {
               qDebug() << "ERROR: " << query.lastError().text();
               //qFatal(QString("One of the query failed to execute."
                 //          " Error detail: " + query.lastError().text()).toLocal8Bit());
                resultado ="no";
           }
           query.finish();
       }
return resultado;
}

