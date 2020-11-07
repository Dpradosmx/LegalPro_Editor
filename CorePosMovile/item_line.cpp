#include "item_line.h"

item_line::item_line()
{



}

void item_line::set_item_line(Item art,double unit){
    set_articulo(art);
    set_unitario(unit);

    QMap<QString,QVariant> articulo_en_linea = articulo.get_item().toMap();
    //impuestos = articulo.get_item_tax();

    double precio_u = art.precio;
    double preciototal = articulo_en_linea.value("total_tax").toDouble()*unit;
    set_importe(preciototal);
    set_grupo_impuestos(articulo_en_linea.value("id_mrhrc_gp").toString());
    set_tipo_renglon("ITEM");
    double total_de_tax=preciototal-precio_u*unit;
    set_titulo(articulo_en_linea.value("nm_item").toString());
    QString xml;
    xml="<SaleReturnLineItem><ID_ITM>"+articulo_en_linea.value("id_itm").toString()+"</ID_ITM>";
    xml+="<ID_GP_TX>"+articulo_en_linea.value("id_gp_tx").toString()+"</ID_GP_TX> <TY_ITM>"+articulo_en_linea.value("ty_itm").toString()+"</TY_ITM>";
    xml+"<TY_ITM_SV></TY_ITM_SV><MO_PRC_REG>"+QString::number(precio_u)+"</MO_PRC_REG><FOOD_STAMP>"+articulo_en_linea.value("food_stamp").toString()+"</FOOD_STAMP>";
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
    xml+="</SaleReturnLineItem>";

}
