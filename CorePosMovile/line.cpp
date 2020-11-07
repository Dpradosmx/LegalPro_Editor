#include "line.h"


line::line()
{

}

void line::set_line(Item art,double unit){//linea venta
    set_articulo(art);
    set_unitario(unit);
    set_cancelable(true);
    set_cambio_precio("");//siempre que se crea linea

    //problema, implicado loggin process, item price, retailtransaction
    QMap<QString,QVariant> articulo_en_linea = articulo.get_item().toMap();
    qDebug() << "line.cpp::Setline() antes de llamar a los impuestos";
//    impuestos =articulo.get_item_tax();
    qDebug() << "line.cpp::Setline() despues de llamar a los impuestos";


    double precio_u = art.precio;
    double preciototal = precio_u*unit;
    set_precio_unitario(precio_u);
    set_importe(preciototal);
    set_grupo_impuestos(articulo_en_linea.value("id_mrhrc_gp").toString());
    set_tipo_renglon("VE");
    double total_de_tax=articulo_en_linea.value("total_tax").toDouble()*unit;
    set_titulo(articulo_en_linea.value("nm_itm").toString());
    total_tax=articulo_en_linea.value("total_tax").toDouble();
    QString xml;
    xml="<SaleReturnLineItem><ID_ITM>"+articulo_en_linea.value("id_itm").toString()+"</ID_ITM>";
    xml+="<ID_GP_TX>"+articulo_en_linea.value("id_gp_tx").toString()+"</ID_GP_TX> <TY_ITM>"+articulo_en_linea.value("ty_itm").toString()+"</TY_ITM>";
    xml+="<TY_ITM_SV></TY_ITM_SV><MO_PRC_REG>"+QString::number(precio_u)+"</MO_PRC_REG><FOOD_STAMP>"+articulo_en_linea.value("food_stamp").toString()+"</FOOD_STAMP>";
    xml+="<CLIENTE>N</CLIENTE><MO_PRC_ACT>"+QString::number(precio_u)+"</MO_PRC_ACT><MO_EXTND>"+QString::number(get_importe())+"</MO_EXTND>";
    xml+="<QU_ITM_LM_RTN_SLS>"+QString::number(get_unitario())+"</QU_ITM_LM_RTN_SLS><QTY_ITM>"+QString::number(get_unitario())+"</QTY_ITM>";
    xml+="<TaxGroupRule><ID_ATHY_TX>"+impuestos.id_athy_tx+"</ID_ATHY_TX><ID_GP_TX>"+impuestos.id_gp_tx+"</ID_GP_TX><AI_CMPND>"+impuestos.ai_cmpnd+"</AI_CMPND>";
    for(int x=0;x<impuestos.impuestos.length();x++){
    xml+="<TaxRateRule><ID_ATHY_TX>"+impuestos.id_athy_tx+"</ID_ATHY_TX>"+"<ID_GP_TX>"+impuestos.id_gp_tx+"</ID_GP_TX>";
    xml+="<ID_GP_TX>"+impuestos.id_gp_tx+"</ID_GP_TX>"+"<AI_TX_RT_RU>"+impuestos.impuestos.at(x).value("ai_tx_rt_ru").toString()+"</AI_TX_RT_RU>";
    xml+="<TY_TX_RT_RU>"+impuestos.impuestos.at(x).value("ty_tx_rt_ru").toString()+"</TY_TX_RT_RU>"+"<MO_TXBM_MNM>"+impuestos.impuestos.at(x).value("mo_txbn_mnm").toString()+"</MO_TXBM_MNM>";
    xml+="<MO_TXBL_MXM>"+impuestos.impuestos.at(x).value("mo_txbl_mxm").toString()+"</MO_TXBL_MXM>"+"<MO_RT_TX>"+impuestos.impuestos.at(x).value("mo_rt_tx").toString()+"</MO_RT_TX>";
    xml+="<PE_RT_TX>"+impuestos.impuestos.at(x).value("pe_rt_tx").toString()+"</PE_RT_TX></TaxRateRule>";
    }
    xml+="</TaxGroupRule>";
    xml+="<SaleReturnTaxLineItem><ID_ATHY_TX>"+impuestos.id_athy_tx+"</ID_ATHY_TX>";
    xml+="<ID_GP_TX>"+impuestos.id_gp_tx+"</ID_GP_TX>";
    xml+="<MO_TXBL_RTN_SLS>"+QString::number(precio_u,'f',2)+"</MO_TXBL_RTN_SLS>";
    xml+="<MO_TX_RTN_SLS>"+QString::number(total_de_tax,'f',2)+"</MO_TX_RTN_SLS></SaleReturnTaxLineItem></SaleReturnLineItem>";
    set_xml(xml);
    qDebug() << "line.cpp:: set_line() " <<get_importe() << " " << get_titulo() << " " << get_unitario() << " " << get_tipo_renglon();

}


void line::set_line(QString titulo_line,double importe){//linea descuento
    set_titulo(titulo_line);
    set_unitario(0);
    set_importe(importe);
    set_grupo_impuestos("");
    set_tipo_renglon("DESC");//NO HAY
    set_cancelable(true);
    set_cambio_precio("");
    total_tax=0;

}

void line::set_line(QString titulo_line,QString tipo_pago,double importe){//linea pago
    set_titulo(titulo_line);
    set_unitario(0);
    set_importe(importe);
    set_grupo_impuestos("");
    set_precio_unitario(importe);
    set_tipo_renglon("TE");//COBRO PA
    set_tipo_pago(tipo_pago);
    set_cancelable(true);
    set_cambio_precio("");
    total_tax=0;
    QString xml;
    xml=" <TenderLineItem><TY_TND>"+tipo_pago+"</TY_TND>";
    xml+="<MO_FRG_CY>"+QString::number(importe)+"</MO_FRG_CY>"+"<MO_ITM_LN_TND>"+QString::number(importe)+"</MO_ITM_LN_TND></TenderLineItem>";
    set_xml(xml);
    qDebug() << "line.cpp:: linea de pago" <<get_importe() << " " << get_titulo() << " " << get_unitario() << " " << get_tipo_renglon();

}

void line::set_line(line linea, int index){//linea de cancelacion
    //2020 cambia las características de la linea a cancelado
    set_titulo(" Cancelacion de linea #"+QString::number(index));
    set_unitario(0);
    set_importe(linea.get_importe()*-1);
    set_precio_unitario(linea.get_importe()*-1);
    set_grupo_impuestos("");
    set_cambio_precio("");
    set_tipo_renglon("AN");
    set_cancelable(false);
    set_cancelacion(true);
    QString xml;//es anulacion, tiene bandera en la transaccion
    total_tax=0;
}

void line::set_line(double importe){//linea cambio
    set_titulo("Cambio");
    set_unitario(0);
    set_importe(importe);
    set_precio_unitario(importe);
    set_grupo_impuestos("");
    set_cambio_precio("");
    set_tipo_renglon("CH");
    set_tipo_pago("CASH");
    set_cancelable(false);
    total_tax=0;
    QString xml;
    xml=" <TenderChangeLineItem><TY_TND>CASH</TY_TND>";
    xml+="<MO_TND_FN_TRN>"+QString::number(importe)+"</MO_TND_FN_TRN></TenderChangeLineItem>";
    set_xml(xml);
    qDebug() << "line.cpp::setline() linea de cambio" << get_importe() << " " << get_titulo() << " " << get_unitario() << " " << get_tipo_renglon();

}

void line::set_line(double importe, QString tipo){
    set_titulo("Deposito de envio ");
    set_unitario(1);
    set_importe(importe);
    set_cambio_precio("");
    set_precio_unitario(importe);
    set_grupo_impuestos("");
    set_tipo_renglon("PA");//pago
    set_tipo_pago(tipo);
    set_cancelable(false);
    total_tax=0;
    QString xml;
    xml=" <TenderLineItem><TY_TND>TE</TY_TND>";
    xml+="<MO_FRG_CY>"+QString::number(importe)+"</MO_FRG_CY>"+"<MO_ITM_LN_TND>"+QString::number(importe)+"</MO_ITM_LN_TND></TenderLineItem>";
    set_xml(xml);
    qDebug() << "line.cpp:: linea de cambio" <<get_importe() << " " << get_titulo() << " " << get_unitario() << " " << get_tipo_renglon();


}
