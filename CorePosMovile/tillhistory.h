#ifndef TILLHISTORY_H
#define TILLHISTORY_H


class tillhistory
{
public:
    tillhistory();
    int id_rpsty_tnd ;
                    int qu_sls_itm ;//lineas de venta con articulo
                    int qu_void_itm;//lineas anuladas
                    int qu_void_itm_tr;//ventas canceladas
                    int qu_rtn_itm ;//cantidad de articulos devueltos
                    int qu_sls_svc ;//cantidad de servicios vendidos
                    int qu_tran ;//cantidad de transacciones
                    int qu_tran_no_sale ;//cantidad de transacciones sin venta
                    int qu_tran_void ;//cantidad de transacciones canceladas

                    float cu_sls_itm ;//importe de ventas, no servicios, incluye anulados
                    float cu_void_itm ;//importe de lineas anuladas
                    float cu_rtn_itm ;//importe de articulos devueltos
                    float cu_void_itm_tr ;// importe ventas canceladas
                    float cu_sls_svc ;//importe de servicios vendidos

                    float cu_sls_tx_itm ;//importe de tax lineas de venta con articulo
                    float cu_void_tx_itm ;//importe de tax lineas anuladas
                    float cu_rtn_tx_itm ;//importe de tax de articulos devueltos
                    float cu_void_tx_itm_tr ;//importe de tax ventas canceladas
                    float cu_sls_tx_svc ;//importe de tax de servicios vendidos
};

#endif // TILLHISTORY_H
