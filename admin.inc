
/*

            NESCESSARIO BLIBIOTECA YSI

            easy dialog

            YSI

*/



#include <YSI_Coding\y_hooks>


/*

        coloque em sua pinfo                   ADMIN  


enum pinfo {
    ADMIN
};
new PlayerInfo[MAX_PLAYERS][pinfo];
 

*/


/*                                  Natives 

                            native SetAdmin(playerid, level);
                            native AvisarAdmins(COLOR, const string[], level);
                            native AdminsCargos(playerid);

*/

#define TOKEN_ADMIN "ZXY9" // defina o token de login admin

//comandos

CMD:padmin(playerid){
    return Dialog_Show(playerid, D_ADMIN, DIALOG_STYLE_INPUT, "Token Admin","Digite o token admin abaixo","Confirmar"," Sair");//retorna dialog pra digita o token
}
Dialog:D_ADMIN(playerid, response, listitem, inputtext[]) {

    if(!response) return true;

    if (strcmp(inputtext, TOKEN_ADMIN, true) == 0) { //sucess

        PlayerInfo[playerid][ADMIN] = 7;
        SendClientMessage(playerid, -1, va_return("Você se tornou um admin Cargo %s", AdminsCargos(playerid)));
        AvisarAdmins(-1, va_return("blabla pop desehi %s", PlayerName(playerid)), 1);
        
    }else{ //fail

        Dialog_Show(playerid, D_ADMIN, DIALOG_STYLE_INPUT, "Token Admin","Digite o token admin abaixo","Confirmar"," Sair");
        SendClientMessage(playerid, -1,"Token Invalido"); //token digitado e diferente do definido
    }
    return 1;
}
CMD:admins(playerid) {

    new str[250]; 
    new count = 0; 

    format(str, sizeof(str), "Nome\t\tCargo\n");
    foreach(new i: Player) {
        if(IsPlayerConnected(i) && PlayerInfo[i][ADMIN] > 0) { //se existir algum adm conectado
            new adminCargo[25];
            strmid(adminCargo, AdminsCargos(i), 0, sizeof(adminCargo));//puxa todos cargos
            Dialog_Show(playerid, D_ADMINS_ON, 5, "Admins", va_return("%s%s\t%s\n", str, PlayerName(i), adminCargo), "Fechar", ""); //dialog de exibiçao
            count++;
        }
    }
    if (count == 0) { strcat(str, "Nao tem nenhum administrador Online\n"); }
    return 1; 
}

//stocks avisar admins somente
AvisarAdmins(COLOR, const string[], level){
	foreach(new i: Player){
		if(IsPlayerConnected(i)){
            if(PlayerInfo[i][ADMIN] >= level) { SendClientMessage(i, COLOR, string); } //FEITO mensagem recebida
		}
	}
    return 1;
}		

//cargos defina o level eo nome do cargo ex
// 1 = 'staff normal'

stock AdminsCargos(playerid) {
    new str[50];
    switch (PlayerInfo[playerid][ADMIN]) {
        case 1: str = "{B0C4DE}Aprendiz"; 
        case 2: str = "{4682B4}Operador"; 
        case 3: str = "{2E8B57}Intermediário";
        case 4: str = "{DAA520}Diretor"; 
        case 5: str = "{FFD700}Gerente"; 
        case 6: str = "{FF4500}Dono"; 
        case 7: str = "{8B0000}Slow"; 
        default: str = "{FFFFFF}Sem Cargo"; 
    }
    return str;
}

//setar admin no player ex comando dar admin ou remover slr
stock SetAdmin(playerid, level) {
    if (level < 0 || level > 7) return 0; 
    PlayerInfo[playerid][pAdmin] = level; 
    SendClientMessage(playerid, va_return("Seu cargo atual é: %s", AdminsName(playerid)));
    return 1; 
}
