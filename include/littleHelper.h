#ifndef LITTLE_HELPER_H
#define LITTLE_HELPER_H



/**
 * @brief Nastaví bit na zadané pozici v registru.
 * @param REG Registr, ve kterém se má bit nastavit.
 * @param pos Pozice bitu, který se má nastavit (0-31 pro 32-bitový registr).
 * @details Makro provádí bitovou operaci OR s posunutou jedničkou.
 *          Nastavený bit zůstane nastaven na logickou 1.
 * @note Nedochází ke kontrole typu nebo rozsahu parametrů.
 * @warning Ujistěte se, že pozice je platná pro daný registr.
 */
#define setBitInRegister(REG, pos)  						REG |= 1 << pos
#define clearBitInRegister(REG, pos)  						REG &= ~(1 << pos)
#define toogleBitInRegister(REG, pos)  						REG ^= 1 << pos

/**
 * @brief nastaví vicebitovou hodnotu v registru na základě zadané masky hodnoty a pozice.
 * @param REG Registr, ve kterém se má hodnota nastavit.
 * @param DATA Data, která se má nastavit.
 * @param MASK Maska určující, které bity se mají změnit. Maska není posunuta, ale je zarovnána na pozici 0.
 * @param pos Pozice bitů, které se mají změnit (0-31 pro 32-bitový registr).
 * @details Makro připraví data na pozici a 
 * @note Nedochází ke kontrole typu nebo rozsahu parametrů.
 * @warning Ujistěte se, že pozice je platná pro daný registr.
 */
#define changeMultipleBitInRegister(REG, DATA, MASK, pos)   REG = (DATA << pos) | (REG & (~(MASK & REG)))
#define setMultipleBitsInRegister(REG,DATA,MASK)			REG = (DATA & (~MASK)) | (DATA & MASK)

__attribute__((optimize("O0"))) void heavyFunction() 
{
    for(int i = 0;i < 2000000; i++){}
}







#endif
