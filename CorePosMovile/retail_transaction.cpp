#include "retail_transaction.h"
#include "till_tender.h"
#include "utilerias.h"

retail_Transaction::retail_Transaction()
{
    desglosaimpuestos=false;
    UPagoFS="";
    settings.setUp();
    flDevolucion = false;
}


QMap<QString,QVariant> retail_Transaction::getTotales()
{
    Utilerias u;
    QMap<QString,QVariant> Totales;

    Totales["Country"]=settings.getCountry();
    Totales["NoRenglones"]=QString::number(rt_lineitem.length());
    Totales["startDate"]=ts_trn_bgn;
    if(cliente != NULL){
        Totales["idCliente"] = QString::number(cliente->get_idCliente());
        Totales["nmClients"] = cliente->get_nmCliente();
    }
    else
    {
        Totales["idCliente"] = "-1";
        Totales["nmClients"] = "";
    }
    Totales["impuestoPrecioOriginal"] = settings.getImpuestoPOrig();
    Totales["Suma"] = u.FormatoNumero(total_v,8,2);
    Totales["Impuesto"] = u.FormatoNumero(total_impuesto,8,2);
    qDebug() << "retail_Transaction::getTotales() " << u.FormatoNumero(total_impuesto,8,2);
    Totales["Total"] = u.FormatoNumero(total_v,8,2);
    Totales["Pagado"] = u.FormatoNumero(total_pagado,8,2);
    Totales["PagadoFS"] = u.FormatoNumero(total_pagadofs,8,2);
    Totales["TotalFS"] = u.FormatoNumero(total_vfs,8,2);
    Totales["Tax"] = u.FormatoNumero(total_impuesto,8,2);
    Totales["TaxFS"] = u.FormatoNumero(total_impuestofs,8,2);
    Totales["APagar"] = u.FormatoNumero(total_v - total_pagado,8,2);
    Totales["APagarFS"] = u.FormatoNumero(total_vfs -total_pagadofs,8,2);;
    Totales["SubsidioTaxFS"] = u.FormatoNumero(total_impuesto-total_impuestofs,8,2);;
    Totales["UPagoFS"] = UPagoFS;
    Totales["NoRenglones"]=rt_lineitem.length();
    return Totales;
}


QMap<QString,QVariant> retail_Transaction::add_line(RT_LineItem* linea)
{
    QMap<QString,QVariant> resultado;
    if(rt_lineitem.length()==0)
    {
        ts_trn_bgn= QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    }
    rt_lineitem.append(linea);
    linea->set_line(rt_lineitem.length());
    resultado["titulo"]= linea->get_titulo();
    resultado["ln"]=rt_lineitem.length();
    if(linea->get_ty_ln_item()=="VE")
    {
        linea->add(Taxes);
        resultado["importe"]=u.FormatoNumero(linea->get_importe(),10,2);
        resultado["precio_unitario"]=u.FormatoNumero(linea->get_precio_unitario(),10,4);
        resultado["unitario"]= u.FormatoNumero(linea->get_cantidad(),4,3);
        total_impuesto+=linea->get_total_tax();
        total_v+=linea->get_importe();
        total_impuestofs+=linea->get_total_taxfs();
        total_vfs+=linea->get_importefs();
        qDebug()<< "array "<<linea->get_imagenes();
        resultado["imagenes"]=linea->imagenes;
    }
    else
        if(linea->get_ty_ln_item()=="TE")
        {
            resultado["importe"]=u.FormatoNumero(linea->get_total_pagado(),10,2);
            resultado["precio_unitario"]="";//u.FormatoNumero(linea->get_precio_unitario(),10,4);
            resultado["unitario"]= "";//u.FormatoNumero(linea->get_cantidad(),4,3);
            total_pagado+=linea->get_total_pagado()-linea->get_total_cambio();
            total_pagadofs+=linea->get_total_pagadofs()-linea->get_total_cambiofs();
            tender.addTillTender(linea,"+");
        }
        else
            if(linea->get_ty_ln_item() == "CH")
            {
                resultado["importe"]=u.FormatoNumero(linea->get_total_pagado(),10,2);
                resultado["precio_unitario"]="";//u.FormatoNumero(linea->get_precio_unitario(),10,4);
                resultado["unitario"]= "";//u.FormatoNumero(linea->get_cantidad(),4,3);
                total_pagado+=linea->get_total_pagado()-linea->get_total_cambio();
                total_pagadofs+=linea->get_total_pagadofs()-linea->get_total_cambiofs();
                tender.addTillTender(linea,"+");
            }
    qDebug() << "retail_Transaction::add_line 5";
    resultado["Suma"] = u.FormatoNumero(total_v+total_impuesto,8,2);
    resultado["Impuesto"] = u.FormatoNumero(total_impuesto,8,2);
    resultado["Total"] = u.FormatoNumero(total_v,8,2);
    resultado["Pagado"] = u.FormatoNumero(total_pagado,8,2);
    resultado["PagadoFS"] = u.FormatoNumero(total_pagadofs,8,2);
    resultado["TotalFS"] = u.FormatoNumero(total_vfs,8,2);
    resultado["Tax"] = u.FormatoNumero(total_impuesto,8,2);
    resultado["TaxFS"] = u.FormatoNumero(total_impuestofs,8,2);
    resultado["APagar"] = u.FormatoNumero(total_v - total_pagado,8,2);
    resultado["APagarFS"] = u.FormatoNumero(total_vfs -total_pagadofs,8,2);;

    resultado["suma"]=u.FormatoNumero((total_v - total_impuesto),8,2);
    resultado["total_venta"]=u.FormatoNumero(total_v,8,2);
    resultado["total_impuesto"]=u.FormatoNumero(total_impuesto,8,2);
    resultado["pagado"]=u.FormatoNumero(total_pagado,8,2);
    resultado["total_a_pagar"]=u.FormatoNumero((total_v-total_pagado),8,2);
    resultado["sumafs"]=u.FormatoNumero((total_vfs - total_impuestofs),8,2);
    resultado["total_ventafs"]=u.FormatoNumero(total_vfs,8,2);
    resultado["total_impuestofs"]=u.FormatoNumero(total_impuestofs,8,2);
    resultado["pagadofs"]=u.FormatoNumero(total_pagadofs,8,2);
    resultado["total_a_pagarfs"]=u.FormatoNumero((total_vfs-total_pagadofs),8,2);
    resultado["cambios"]="";

    qDebug() << "retail_Transaction::add_line 6";
    return resultado;
}


QMap<QString,QVariant> retail_Transaction::add_line_cancel(int NoLinea)
{
    QMap<QString,QVariant> resultado;
    RT_LineItem* linea;
    RT_LineItem* cancelada;

    linea = new RT_LineItem(rt_lineitem.length());
    cancelada = get_line(NoLinea);
    linea->do_cancel(NoLinea);//Indica que linea es la que se está cancelando
    cancelada->do_cancel(rt_lineitem.length());
    rt_lineitem.append(linea);
    resultado["importe"]=" ";
    resultado["precio_unitario"]=" ";
    resultado["titulo"]= "Cancela linea: " +QString::number(NoLinea+1);
    resultado["unitario"]= " ";
    resultado["ln"]=rt_lineitem.length();
    if(cancelada->get_tipo_renglon() ==  "VE")
    {
        cancelada->subtract(Taxes);
        total_impuesto-=cancelada->get_total_tax();
        qDebug() << "retail_Transaction::add_line" << QString::number(cancelada->get_total_tax(),'f',6) <<" impuesto";
        total_v-=cancelada->get_importe();
    }
    else
    {
        if(cancelada->get_tipo_renglon() =="TE")
        {
           tender.addTillTender(cancelada,"-");
           total_pagado-=cancelada->get_total_pagado();
        }
    }
    resultado["suma"]=u.FormatoNumero((total_v - total_impuesto),8,2);
    resultado["total_venta"]=u.FormatoNumero(total_v,8,2);
    resultado["total_impuesto"]=u.FormatoNumero(total_impuesto,8,2);
    resultado["pagado"]=u.FormatoNumero(total_pagado,8,2);
    resultado["total_a_pagar"]=u.FormatoNumero((total_v-total_pagado),8,2);
    resultado["sumafs"]=u.FormatoNumero((total_vfs - total_impuestofs),8,2);
    resultado["total_ventafs"]=u.FormatoNumero(total_vfs,8,2);
    resultado["total_impuestofs"]=u.FormatoNumero(total_impuestofs,8,2);
    resultado["pagadofs"]=u.FormatoNumero(total_pagadofs,8,2);
    resultado["total_a_pagarfs"]=u.FormatoNumero((total_vfs-total_pagadofs),8,2);
    return resultado;
}

QMap<QString,QVariant> retail_Transaction::do_cambio_precio(int indice, QVariant param)
{
    QMap<QString,QVariant> param1=param.toMap();
    QMap<QString,QVariant> resultado;

    RT_LineItem* linea;
    linea = get_line(indice);
    linea->subtract(Taxes);
    total_impuesto-=linea->get_total_tax();
    total_v-=linea->get_importe();
    linea->CambioPrecio(param1.value("precio_Nuevo").toDouble(0),param1.value("hora").toString(),param1.value("id_supervisor").toString(),param1.value("razon").toString());
    total_impuesto+=linea->get_total_tax();
    total_v+=linea->get_importe();
    linea->add(Taxes);

    resultado["indice"]=QString::number(indice);
    resultado["ln"]=QString::number(indice);
    resultado["importe"]=u.FormatoNumero(linea->get_importe(),10,2);
    resultado["precio_unitario"]=u.FormatoNumero(linea->get_precio_unitario(),10,4);
    resultado["suma"]= u.FormatoNumero((total_v - total_impuesto),8,2);
    resultado["textQuantity"]=u.FormatoNumero(linea->get_cantidad(),4,3);
    resultado["total_venta"]=u.FormatoNumero(total_v,8,2);
    resultado["total_impuesto"]=u.FormatoNumero(total_impuesto,8,2);
    resultado["pagado"]=u.FormatoNumero(total_pagado,8,2);
    resultado["total_a_pagar"]=u.FormatoNumero((total_v-total_pagado),8,2);
    resultado["sumafs"]=u.FormatoNumero((total_vfs - total_impuestofs),8,2);
    resultado["total_ventafs"]=u.FormatoNumero(total_vfs,8,2);
    resultado["total_impuestofs"]=u.FormatoNumero(total_impuestofs,8,2);
    resultado["pagadofs"]=u.FormatoNumero(total_pagadofs,8,2);
    resultado["total_a_pagarfs"]=u.FormatoNumero((total_vfs-total_pagadofs),8,2);
    return resultado;
}

QMap<QString,QVariant> retail_Transaction::do_cambios(int indice, QVariant param)
{
    QMap<QString,QVariant> param1=param.toMap();
    QMap<QString,QVariant> resultado;

    RT_LineItem* linea;
    linea = get_line(indice);
    linea->subtract(Taxes);
    total_impuesto-=linea->get_total_tax();
    total_v-=linea->get_importe();
    //linea->CambioPrecio(param1.value("precio_Nuevo").toDouble(0),param1.value("hora").toString(),param1.value("id_supervisor").toString(),param1.value("razon").toString());
    linea->set_cambios(param1.value("cambios").toString());
    total_impuesto+=linea->get_total_tax();
    total_v+=linea->get_importe();
    linea->add(Taxes);

    resultado["indice"]=QString::number(indice);
    resultado["ln"]=QString::number(indice);
    resultado["importe"]=u.FormatoNumero(linea->get_importe(),10,2);
    resultado["precio_unitario"]=u.FormatoNumero(linea->get_precio_unitario(),10,4);
    resultado["suma"]= u.FormatoNumero((total_v - total_impuesto),8,2);
    resultado["textQuantity"]=u.FormatoNumero(linea->get_cantidad(),4,3);
    resultado["total_venta"]=u.FormatoNumero(total_v,8,2);
    resultado["total_impuesto"]=u.FormatoNumero(total_impuesto,8,2);
    resultado["pagado"]=u.FormatoNumero(total_pagado,8,2);
    resultado["total_a_pagar"]=u.FormatoNumero((total_v-total_pagado),8,2);
    resultado["sumafs"]=u.FormatoNumero((total_vfs - total_impuestofs),8,2);
    resultado["total_ventafs"]=u.FormatoNumero(total_vfs,8,2);
    resultado["total_impuestofs"]=u.FormatoNumero(total_impuestofs,8,2);
    resultado["pagadofs"]=u.FormatoNumero(total_pagadofs,8,2);
    resultado["total_a_pagarfs"]=u.FormatoNumero((total_vfs-total_pagadofs),8,2);
    qDebug()<<"Los cambios "<<linea->get_cambios();
    return resultado;
}

QMap<QString,QVariant> retail_Transaction::add_line(line linea)
{
    QMap<QString,QVariant> resultado;
    tx="";
    Utilerias u;

    qDebug() << "Retail_transaction::addline";
    lineas.append(linea);
    if(linea.get_tipo_renglon().compare("VE")==0){
        //tax=linea.get_articulo().get_item_tax();

        total_articulos+=linea.get_unitario();
        for(int z=0;z<tax.impuestos.length();z++){
            if(tax.impuestos.at(z).value("ty_tx_rt_ru").toString().compare("PE")==0){
                double impuesto=tax.impuestos.at(z).value("pe_rt_tx").toDouble();
            total_impuestos.add_to_list(tax.impuestos.at(z).value("cd_rcpt_prn").toString()+" "+tax.impuestos.at(z).value("nm_gp_tx").toString(),impuesto,linea.get_articulo().precio,"PE");
            tx+=tax.impuestos.at(z).value("cd_rcpt_prn").toString();
            }
            else{
                double impuesto=tax.impuestos.at(z).value("mo_rt_tx").toDouble();
            total_impuestos.add_to_list(tax.impuestos.at(z).value("cd_rcpt_prn").toString()+" "+tax.impuestos.at(z).value("nm_gp_tx").toString(),impuesto,linea.get_articulo().precio,"FII");
            tx+=tax.impuestos.at(z).value("cd_rcpt_prn").toString();
            }
        }
       articulos_impresion+=tik.text_ticket(linea.get_titulo(),u.FormatoNumero(linea.get_unitario(),8,4),u.FormatoNumero(linea.get_importe(),10,2),48,tx,u.FormatoNumero(linea.get_precio_unitario(),8,4))+"\n";
       // qDebug() << articulos_impresion <<" articulos de impresion";
    }
    if(linea.get_tipo_renglon().compare("TE")==0){
       total_pagado+=linea.get_importe();/*
       if(linea.get_tipo_pago().compare("CASH")==0){total_chash+=linea.get_precio_unitario();}
       if(linea.get_tipo_pago().compare("CCAR")==0){total_card+=linea.get_precio_unitario();}
       if(linea.get_tipo_pago().compare("CHEC")==0){total_check+=linea.get_precio_unitario();}
       if(linea.get_tipo_pago().compare("FSTP")==0){total_food+=linea.get_precio_unitario();}*/
       pagos_impresion+=tik.text_lista(linea.get_titulo(),"$ "+u.FormatoNumero(linea.get_importe(),8,4),48)+'\n';
        qDebug() << pagos_impresion <<" articulos de impresion";
    }

    if(linea.get_tipo_renglon().compare("AN")==0){
        articulos_impresion+=tik.text_lista(linea.get_titulo(),QString::number(linea.get_importe()),48)+"\n";
    }

    if(linea.get_tipo_renglon().compare("CH")==0){
        pagos_impresion+=tik.text_lista(linea.get_titulo(),"$ "+u.FormatoNumero(linea.get_importe(),8,2),48)+"\n";
    }

    if(linea.get_tipo_renglon().compare("EN")==0){//ENVIO
        articulos_impresion+=tik.text_ticket(linea.get_titulo(),u.FormatoNumero(linea.get_unitario(),8,4),u.FormatoNumero(linea.get_importe(),10,2),48,tx,u.FormatoNumero(linea.get_precio_unitario(),8,4))+"\n";
        //qDebug() << articulos_impresion <<" articulos de impresion";
    }
    //poner la construccion del ticket de compra.

    //qDebug() <<lineas.length() <<"tamaño de lineas";
    resultado["importe"]=u.FormatoNumero(linea.get_importe(),10,2);
    qDebug() << linea.get_importe() <<" importe";
    resultado["precio_unitario"]=u.FormatoNumero(linea.get_precio_unitario(),10,4);
    qDebug() << linea.get_precio_unitario() <<" precio unitario";
    resultado["titulo"]= linea.get_titulo();
    qDebug() << linea.get_titulo() <<" titulo";
    //Unitario son las cantidades.
    resultado["unitario"]= u.FormatoNumero(linea.get_unitario(),4,3);
    qDebug() << linea.get_unitario();
    resultado["ln"]=lineas.length();

    if(linea.get_tipo_renglon().compare("CH")!=0 && linea.get_tipo_renglon().compare("TE")!=0){
    total_v+=linea.get_importe();
    }
    total_impuesto+=linea.total_tax;
    resultado["suma"]=u.FormatoNumero((total_v - total_impuesto),8,2);
    resultado["total_venta"]=u.FormatoNumero(total_v,8,2);
    resultado["total_impuesto"]=u.FormatoNumero(total_impuesto,8,2);
    resultado["pagado"]=u.FormatoNumero(total_pagado,8,2);
    resultado["total_a_pagar"]=u.FormatoNumero((total_v-total_pagado),8,2);
    return resultado;

}


QMap<QString,QVariant> retail_Transaction::actualizar(){
    QMap<QString,QVariant> a;
    double precio=0;
    Utilerias u;

    qDebug() << "Retail_transaction::actualizar";
    articulos_impresion="";
    total_v=0;
    for(int x=0;x<lineas.length();x++){
        precio=lineas.at(x).precio_unitario;
       articulos_impresion+=tik.text_ticket(lineas.at(x).get_titulo(),u.FormatoNumero(lineas.at(x).get_unitario(),8,4),u.FormatoNumero(lineas.at(x).get_importe(),10,2),48,tx,u.FormatoNumero(precio,8,4))+"\n";
       total_v+=lineas.at(x).get_importe();
    }
    qDebug()<<articulos_impresion<<total_v;
    a["suma"]=u.FormatoNumero((total_v - total_impuesto),8,2);
    a["total_venta"]=u.FormatoNumero(total_v,8,2);
    a["total_impuesto"]=u.FormatoNumero(total_impuesto,8,2);
    a["pagado"]=u.FormatoNumero(total_pagado,8,2);
    a["total_a_pagar"]=u.FormatoNumero((total_v-total_pagado),8,2);
 return a;
}

QMap<QString,QString> show_Line(line linea){
    QMap<QString,QString> display;
    return display;
}

void retail_Transaction::inicializar(bool wdesglosaimpuestos, RT_Total_Tax* wTaxes){
    //qDebug() << "Retail_transaction::inicializar";

    int i;

    desglosaimpuestos=wdesglosaimpuestos;
    /*
    total_chash=0;
    total_card=0;
    total_vale=0;
    total_food=0;
    total_check=0;
*/

    total_pagado=0;
    total_impuesto=0;
    total_v=0;
    total_articulos=0;
    total_pagadofs=0;
    total_impuestofs=0;
    total_vfs=0;
    total_articulosfs=0;
    string_impresion="";
    articulos_impresion="";
    pagos_impresion="";
    lineas.clear();    
    total_impuestos.clear();
    if(Taxes == NULL)
        Taxes=new RT_Total_Tax(wTaxes);
    else
    {
        Taxes->inicia();
    }
    if (cliente != NULL)
    {
        delete cliente;
        cliente = NULL;
    }
    i = 0;
    while (i < rt_lineitem.length())
    {
        if(rt_lineitem.at(i) != NULL)
        {
            delete rt_lineitem.at(i);
        }
        i++;
    }
    rt_lineitem.clear();
}

QString retail_Transaction::do_transaction(){

    QString xmlf="";

    qDebug() << "Retail_transaction::do_transaction";
    QString totales1;
    totales1="";
    string_impresion=tik.text_ticket("Descripción","Cant.","Importe",48,"","Unitario")+"\n";
    string_impresion+=get_impresion(true);
    totales1="Subtotal: $"+u.FormatoNumero((total_v-total_impuesto),10,2)+"  ";
    string_impresion+=totales1.rightJustified(46,' ')+"  \n";
    totales1="Total: $"+u.FormatoNumero(total_v,10,2)+"  ";
    string_impresion+=totales1.rightJustified(46,' ')+"  \n";
    string_impresion+=Taxes->Get_PrintLines()+"\n";
    string_impresion+=get_impresion(false);
    qDebug() << "retail_Transaction::do_transaction()";
    for(int i=0;i<rt_lineitem.length();i++){
        xmlf+=rt_lineitem.at(i)->get_XML();
    }
    qDebug() << "retail_Transaction::do_transaction()" << xmlf;
    /*
    for(int x=0;x<lineas.length();x++){
        xmlf+="<AI_LN_ITEM>"+QString::number(x+1)+"</AI_LN_ITEM>";
        if(lineas.at(x).get_tipo_renglon().compare("AN")==0)//si es linea de anulacion
        {
            xmlf+="<AI_LN_ITEM_VD>"+QString::number(lineas.at(x).get_cancelacion())+"</AI_LN_ITEM_VD>";
            xmlf+="<TY_LN_ITEM>AN</TY_LN_ITEM><FL_VD_LN_ITEM>0</FL_VD_LN_ITEM><LU_MTH_LTM_RTL_TRN>1</LU_MTH_LTM_RTL_TRN>";
            xmlf+="</RetailTrsansactionLineItem>";

             continue;
        }
        if(lineas.at(x).get_tipo_renglon().compare("TE")==0)
        {
            //pago a ingresos
            tender.addTillTender(lineas.at(x).get_tipo_pago(),0,u.FormatoNumero(lineas.at(x).get_importe(),10,2),"+");
            xmlf+="<AI_LN_ITEM_VD>0</AI_LN_ITEM_VD>";
            xmlf+="<TY_LN_ITEM>"+lineas.at(x).get_tipo_renglon()+"</TY_LN_ITEM><FL_VD_LN_ITEM>0</FL_VD_LN_ITEM><LU_MTH_LTM_RTL_TRN>true</LU_MTH_LTM_RTL_TRN>";
            xmlf+=lineas.at(x).get_xml();
            xmlf+="</RetailTrsansactionLineItem>";
            continue;
        }
        if(lineas.at(x).get_tipo_renglon().compare("CH")==0){
            //pago a cambios
            tender.addTillTender(lineas.at(x).get_tipo_pago(),1,u.FormatoNumero(lineas.at(x).get_importe(),10,2),"+");
            xmlf+="<AI_LN_ITEM_VD>0</AI_LN_ITEM_VD>";
            xmlf+="<TY_LN_ITEM>"+lineas.at(x).get_tipo_renglon()+"</TY_LN_ITEM><FL_VD_LN_ITEM>0</FL_VD_LN_ITEM><LU_MTH_LTM_RTL_TRN>true</LU_MTH_LTM_RTL_TRN>";
            xmlf+=lineas.at(x).get_xml();
            xmlf+="</RetailTrsansactionLineItem>";
            continue;
        }
        if(lineas.at(x).get_tipo_renglon().compare("PA")==0){
            //pago a depositos
            tender.addTillTender(lineas.at(x).get_tipo_pago(),6,u.FormatoNumero(lineas.at(x).get_importe(),10,2),"+");
            xmlf+="<AI_LN_ITEM_VD>0</AI_LN_ITEM_VD>";
            xmlf+="<TY_LN_ITEM>"+lineas.at(x).get_tipo_renglon()+"</TY_LN_ITEM><FL_VD_LN_ITEM>0</FL_VD_LN_ITEM><LU_MTH_LTM_RTL_TRN>true</LU_MTH_LTM_RTL_TRN>";
            xmlf+=lineas.at(x).get_xml();
            xmlf+="</RetailTrsansactionLineItem>";
            continue;
        }
        xmlf+="<AI_LN_ITEM_VD>0</AI_LN_ITEM_VD>";
        xmlf+="<TY_LN_ITEM>"+lineas.at(x).get_tipo_renglon()+"</TY_LN_ITEM><FL_VD_LN_ITEM>0</FL_VD_LN_ITEM><LU_MTH_LTM_RTL_TRN>1</LU_MTH_LTM_RTL_TRN>";
        xmlf+=lineas.at(x).get_xml();
        xmlf+="</RetailTrsansactionLineItem>";

    }
    */
    return xmlf;
}

QString retail_Transaction::get_impresion(bool venta)
{
    QString resultado;

    resultado = "";
    if(venta)
       qDebug() << "retail_Transaction::get_impresion() verdadero";
    else
        qDebug() << "retail_Transaction::get_impresion() falso";
    for(int x=0;x<rt_lineitem.length();x++){
        resultado += rt_lineitem.at(x)->get_print_line(venta);
    }
    return resultado;
}

void retail_Transaction::set_cliente(QVariant wcliente, QVariant wnmcliente)
{
    cliente = new Cliente(wcliente, wnmcliente);
}

void retail_Transaction::elimina_cliente()
{
    if(cliente!=NULL)
    {
        delete cliente;
        cliente=NULL;
    }
}

int retail_Transaction::get_total_art(){
    return total_articulos;
}

retail_Transaction::~retail_Transaction(){
    int position;

    qDebug() << "retail_Transaction::~retail_Transaction 1";
    if(cliente!=NULL)
    {
        delete cliente;
        cliente = NULL;
    }
    qDebug() << "retail_Transaction::~retail_Transaction 2";
    if(Taxes != NULL)
    {
        delete Taxes;
        Taxes=NULL;
    }
    position = 0;
    while (position < rt_lineitem.length()){
        delete rt_lineitem.at(position);
        position++;
    }
    rt_lineitem.clear();
}

bool retail_Transaction::venta_activa()
{
    return (rt_lineitem.length() > 0);
}

QMap<QString, QVariant> retail_Transaction::getlinea(int i){
    return rt_lineitem.at(i)->getlinea(i);
}

bool retail_Transaction::toggleflDevolucion(){
    flDevolucion=!flDevolucion;
    return flDevolucion;
}

bool retail_Transaction::getflDevolucion(){
    return flDevolucion;
}

bool retail_Transaction::getPosibleNoVenta(){
    bool ret;
    int i;
    i=0; ret = true;
    while (i < rt_lineitem.length())
    {
        if(rt_lineitem.at(i)->get_tipo_renglon()!="AN")
        {
            if(rt_lineitem.at(i)->get_cancelable())
            {
                ret=false;
                i=rt_lineitem.length();
            }
        }
        i++;
    }
    return ret;
}

