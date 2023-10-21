#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h> // CRIAR FUNÇÕES BOOL

// DECLARAÇÃO DAS ESTRUTURAS

struct Reserve
{
    char name_guest[50];
    char name_employee[50];
    int num_hotel;
    int type_room;
    char checkin[12];
    char checkout[12];
    int days;
    float daily;
    float total;
};

struct Suits
{
    int id;
    int available;
    float price;
};

struct Standard
{
    int id;
    int available;
    float price;
};

struct Deluxes
{
    int id;
    int available;
    float price;
};

struct Rooms
{
    struct Suits suits;
    struct Standard standard;
    struct Deluxes deluxes;
};

struct Hotel
{
    int id;
    char name[50];
    int stars;
    struct Rooms rooms;
};


//DECLARAÇÃO DAS VARIÁVEIS GLOBAIS

int GuestOrEmployee = 0;
char nameGuest[50];
char nameEmployee[50];
int optionMenu = 0;
int optionGuest = 0;
int optionEmployees = 0;
int num_reserves = 0;
struct Reserve reserves[45];

// DECLARAÇÃO DOS HÓTEIS

struct Hotel hotel01 = {1, "Hotel Araucária Flat", 5, {{1, 5, 200.00}, {2, 5, 500.00}, {3, 5, 1000.00}}};
struct Hotel hotel02 = {2, "Hotel By Mercure", 4, {{1, 5, 200.00}, {2, 5, 500.00}, {3, 5, 1000.00}}};
struct Hotel hotel03 = {3, "Hotel Confort", 3, {{1, 5, 200.00}, {2, 5, 500.00}, {3, 5, 1000.00}}};


void main()
{
    setlocale(LC_ALL, "Portuguese");
    menu();
}

void showOptions()
{
    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");
    printf("| 1. ENTRAR COMO FUNCIONÁRIO\n");
    printf("| 2. ENTRAR COMO HÓSPEDE\n");
    printf("| 3. SAIR DO SISTEMA\n\n");
    printf("ESCOLHA UM OPÇÃO: ");
    scanf("%i", &optionMenu);
    fflush(stdin);
    system("cls");
}

void menu()
{
    do
    {
        showOptions();
    }
    while(optionMenu != 1 && optionMenu != 2 && optionMenu != 3);


    switch(optionMenu)
    {
    case 1:
        employees();
        break;
    case 2:
        guests();
        break;
    case 3:
        close();
        break;
    }
}


// --------------- MENU FUNCIONÁRIOS ------------------------

float totalRevenueByHotel(struct Hotel hotel)
{
    float revenue = 0;

    for (int i = 0; i < num_reserves; i++)
    {
        if (reserves[i].num_hotel == hotel.id)
        {
            revenue += reserves[i].total;
        }
    }

    return revenue;
}

void generateReport()
{
    int back = 0;

    do
    {
        float totalRevenue = 0;
        int totalReservations = num_reserves;

        for (int i = 0; i < num_reserves; i++)
        {
            totalRevenue += reserves[i].total;
        }

        int totalOccupied1 = 15 - (hotel01.rooms.suits.available + hotel01.rooms.standard.available + hotel01.rooms.deluxes.available);
        int totalOccupied2 = 15 - (hotel02.rooms.suits.available + hotel02.rooms.standard.available + hotel02.rooms.deluxes.available);
        int totalOccupied3 = 15 - (hotel03.rooms.suits.available + hotel03.rooms.standard.available + hotel03.rooms.deluxes.available);

        printf("=========================================\n");
        printf("   RELATÓRIO DE DESEMPENHO DOS HOTÉIS   \n");
        printf("=========================================\n\n");

        printf("Número total de reservas: %d\n", totalReservations);
        printf("Receita total gerada: R$%.2f\n\n", totalRevenue);

        printf("=========================================\n\n");

        // Hotel 01
        printf("Hotel 01: %s\n\n", hotel01.name);
        printf("Número total de reservas: %d\n", totalOccupied1);
        printf("Número de quartos ocupados: %d\n", totalOccupied1);
        printf("Número de quartos disponíveis: %d quartos (%d Suíte | %d Standard | %d Deluxe)\n", 15 - totalOccupied1, hotel01.rooms.suits.available, hotel01.rooms.standard.available, hotel01.rooms.deluxes.available);
        printf("Receita gerada: R$%.2f\n\n", totalRevenueByHotel(hotel01));

        printf("=========================================\n\n");

        // Hotel 02
        printf("Hotel 02: %s\n\n", hotel02.name);
        printf("Número total de reservas: %d\n", totalOccupied2);
        printf("Número de quartos ocupados: %d\n", totalOccupied2);
        printf("Número de quartos disponíveis: %d quartos (%d Suíte | %d Standard | %d Deluxe)\n", 15 - totalOccupied2, hotel02.rooms.suits.available, hotel02.rooms.standard.available, hotel02.rooms.deluxes.available);
        printf("Receita gerada: R$%.2f\n\n", totalRevenueByHotel(hotel02));

        printf("=========================================\n\n");

        // Hotel 03
        printf("Hotel 03: %s\n\n", hotel03.name);
        printf("Número total de reservas: %d\n", totalOccupied3);
        printf("Número de quartos ocupados: %d\n", totalOccupied3);
        printf("Número de quartos disponíveis: %d quartos (%d Suíte | %d Standard | %d Deluxe)\n", 15 - totalOccupied3, hotel03.rooms.suits.available, hotel03.rooms.standard.available, hotel03.rooms.deluxes.available);
        printf("Receita gerada: R$%.2f\n\n", totalRevenueByHotel(hotel03));

        printf("=========================================\n\n");

        printf("DIGITE 2 PARA VOLTAR: ");
        scanf("%i", &back);
        system("cls");
    }
    while(back != 2);

    if(back == 2)
    {
        system("cls");
        showOptionsEmployees();
    }

}


void login()
{

    char user[50];
    char password[8];
    int incorrectPassword = 0;

    do
    {
        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("| DIGITE UM USUÁRIO ADMINISTRADOR: ");
        gets(user);


        if(strcmp(user, "admin") != 0)
        {
            system("cls");
            printf("=========================================\n");
            printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
            printf("=========================================\n\n");
            printf("| USUÁRIO NÃO CADASTRADO!", user);
            sleep(3);
            system("cls");
        }

    }
    while(strcmp(user, "admin") != 0);

    do
    {
        printf("| DIGITE A SENHA: ");
        gets(password);

        if(strcmp(password, "admin123") != 0)
        {
            printf("| SENHA INCORRETA!\n\n");
            incorrectPassword++;

            if(incorrectPassword == 3)
            {
                printf("MUITAS TENTATIVAS ERRADAS!\n");
                printf("VOLTANDO PARA O INÍCIO...");
                sleep(5);
                system("cls");
                menu();
            }
        }


    }
    while(strcmp(password, "admin123") != 0);
}

void showOptionsEmployees()
{
    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");
    printf("| 1. ATRIBUIR RESERVA À UM HÓSPEDE\n");
    printf("| 2. ALTERAR RESERVA\n");
    printf("| 3. VISUALIZAR RESERVAS\n");
    printf("| 4. GERAR RELATÓRIO DAS RESERVAS\n");
    printf("| 5. VOLTAR PARA O MENU\n\n");
    printf("| ESCOLHA UMA OPÇÃO: ");
    scanf("%i", &optionEmployees);
    system("cls");


    switch(optionEmployees)
    {
    case 1:
        addReserve(nameEmployee);
        break;
    case 2:
        changeReservations();
        break;
    case 3:
        viewReservations();
        break;
    case 4:
        generateReport();
        break;
    case 5:
        menu();
        break;
    }
}

void employees()
{
    login();

    GuestOrEmployee = 0;

    system("cls ");
    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");
    printf("SEJA BEM-VINDO!\n\n");
    printf("DIGITE SEU NOME: ");
    gets(nameEmployee);
    system("cls");

    do
    {
        showOptionsEmployees();
    }
    while(optionEmployees != 1 && optionEmployees != 2 && optionEmployees != 3 && optionEmployees != 4 && optionEmployees != 5);

}

// --------------- MENU HÓSPEDES ----------------------------

bool verifyRoom(hotel, room)
{

    switch (hotel)
    {
    case 1:
        switch (room)
        {
        case 1:
            return hotel01.rooms.suits.available > 0;
            break;
        case 2:
            return hotel01.rooms.standard.available > 0;
            break;
        case 3:
            return hotel01.rooms.deluxes.available > 0;
            break;
        }
        break;

    case 2:
        switch (room)
        {
        case 1:
            return hotel02.rooms.suits.available > 0;
            break;
        case 2:
            return hotel02.rooms.standard.available > 0;
            break;
        case 3:
            return hotel02.rooms.deluxes.available > 0;
            break;
        }
        break;

    case 3:
        switch (room)
        {
        case 1:
            return hotel03.rooms.suits.available > 0;
            break;
        case 2:
            return hotel03.rooms.standard.available > 0;
            break;
        case 3:
            return hotel03.rooms.deluxes.available > 0;
            break;
        }
        break;
    }
}


int hotelOptions(hotel)
{

    do
    {
        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("| 1. %s\n", hotel01.name);
        printf("| 2. %s\n", hotel02.name);
        printf("| 3. %s\n\n", hotel03.name);
        printf("| ESCOLHA UM DOS HOTÉIS: ");
        scanf("%d", &hotel);
        system("cls");
    }
    while(hotel != 1 && hotel != 2 && hotel != 3);

    return hotel;
}

int roomOptions(room)
{
    do
    {
        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("| 1. Suíte\n");
        printf("| 2. Standard\n");
        printf("| 3. Deluxe\n\n");
        printf("| SELECIONE O TIPO DE QUARTO: ");
        scanf("%d", &room);
        fflush(stdin);
        system("cls");
    }
    while(room != 1 && room != 2 && room != 3);

    return room;

}

int getDays(days)
{
    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");
    printf("| DIGITE QUANTOS DIAS O QUARTO SERÁ RESERVADO: ");
    scanf("%i", &days);
    fflush(stdin);

    return days;
}

int roomAvailability(hotel, room)
{
    switch(room)
    {
    case 1:
        return verifyRoom(hotel, room) ? 1 : 0;
        break;
    case 2:
        return verifyRoom(hotel, room) ? 1 : 0;
        break;
    case 3:
        return verifyRoom(hotel, room) ? 1 : 0;
        break;
    default:
        printf("OPÇÃO INVÁLIDA");
        sleep(3);
        system("cls");
    }
}

char getCheckin(checkin)
{
    printf("\n| DIGITE A DATA DE CHECK-IN (DD/MM/YYYY): ");
    gets(checkin);

    return checkin;
}

char getCheckout(checkout)
{
    printf("\n| DIGITE A DATA DE CHECKOUT (DD/MM/YYYY): ");
    gets(checkout);
    system("cls");

    return checkout;
}

void addReserve()
{
    char checkin[12];
    char checkout[12];

    int hotel = hotelOptions(hotel);
    int room = roomOptions(room);
    int roomAvailable = roomAvailability(hotel, room);



    if(roomAvailable)
    {

        if(GuestOrEmployee == 0)
        {
            printf("=========================================\n");
            printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
            printf("=========================================\n\n");
            printf("DIGITE O NOME DO HÓSPEDE: ");
            gets(nameGuest);
            system("cls");
        }

        int days = getDays(days);
        getCheckin(checkin);
        getCheckout(checkout);

        if(GuestOrEmployee == 0)
        {
            strcpy(reserves[num_reserves].name_employee, nameEmployee);
        }
        else
        {
            strcpy(reserves[num_reserves].name_employee, "NULL");
        }

        strcpy(reserves[num_reserves].name_guest, nameGuest);
        reserves[num_reserves].num_hotel = hotel;
        reserves[num_reserves].type_room = room;
        reserves[num_reserves].days = days;
        strcpy(reserves[num_reserves].checkin, checkin);
        strcpy(reserves[num_reserves].checkout, checkout);

        switch(room)
        {
        case 1:
            reserves[num_reserves].daily = hotel01.rooms.suits.price;
            break;
        case 2:
            reserves[num_reserves].daily = hotel02.rooms.standard.price;
            break;
        case 3:
            reserves[num_reserves].daily = hotel03.rooms.deluxes.price;
            break;
        }

        reserves[num_reserves].total = reserves[num_reserves].daily * days;

        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("| RESERVA CONCLUÍDA!");
        sleep(3);
        system("cls");

        switch (hotel)
        {
        case 1:
            switch (room)
            {
            case 1:
                hotel01.rooms.suits.available--;
                break;
            case 2:
                hotel01.rooms.standard.available--;
                break;
            case 3:
                hotel01.rooms.deluxes.available--;
                break;
            }
            break;

        case 2:
            switch (room)
            {
            case 1:
                hotel02.rooms.suits.available--;
                break;
            case 2:
                hotel02.rooms.standard.available--;
                break;
            case 3:
                hotel02.rooms.deluxes.available--;
                break;
            }
            break;

        case 3:
            switch (room)
            {
            case 1:
                hotel03.rooms.suits.available--;
                break;
            case 2:
                hotel03.rooms.standard.available--;
                break;
            case 3:
                hotel03.rooms.deluxes.available--;
                break;
            }
            break;
        }


        num_reserves++;
        GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
    }
    else
    {
        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("QUARTO INDISPONÍVEL!");
        sleep(3);
        system("cls");
        addReserve();
    }



}

void showReserves()
{
    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");

    for(int i = 1; i <= num_reserves; i++)
    {
        printf("| %iª Reserva\n\n", i);

        printf("| Nome do hóspede: %s\n", reserves[i - 1].name_guest);

        if(GuestOrEmployee == 0 && strcmp(reserves[i - 1].name_employee, "NULL") != 0)
        {
            printf("| Reserva feita pelo funcionário: %s\n", reserves[i - 1].name_employee);
        }

        switch(reserves[i - 1].num_hotel)
        {
        case 1:
            printf("| Nome do hotel: %s (%i estrelas)\n", hotel01.name, hotel01.stars);
            break;
        case 2:
            printf("| Nome do hotel: %s (%i estrelas)\n", hotel02.name, hotel02.stars);
            break;
        case 3:
            printf("| Nome do hotel: %s (%i estrelas)\n", hotel03.name, hotel03.stars);
            break;
        }

        switch(reserves[i - 1].type_room)
        {
        case 1:
            printf("| Tipo do quarto: Suíte\n");
            break;
        case 2:
            printf("| Tipo do quarto: Standard\n");
            break;
        case 3:
            printf("| Tipo do quarto: Deluxe\n");
            break;
        }

        printf("| Dias reservados: %d\n", reserves[i - 1].days);
        printf("| Data de check-in: %s\n", reserves[i - 1].checkin);
        printf("| Data de checkout: %s\n", reserves[i - 1].checkout);
        printf("| Valor da diária: R$%.2f\n", reserves[i - 1].daily);
        printf("| Valor total da reserva: R$%.2f\n\n", reserves[i - 1].total);
        printf("=========================================\n\n");
    }
}

void viewReservations()
{
    if(num_reserves > 0)
    {
        int back;

        do
        {
            showReserves();
            printf("\n| DIGITE 2 PARA VOLTAR: ");
            scanf("%i", &back);
            system("cls");

        }
        while(back != 2);

        if(back == 2)
        {
            system("cls");
            GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
        }

    }
    else
    {
        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("| AINDA NÃO HÁ RESERVAS!\n");
        sleep(3);
        system("cls");
        GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
    }
}

void changeReservations()
{
    int chooseReserve;
    int changeOption;

    int room;
    char checkin[12];
    char checkout[12];
    int days;

    if(num_reserves > 0)
    {

        do
        {
            showReserves();
            printf("| DIGITE O NÚMERO DA RESERVA QUE DESEJA ALTERAR: ");
            scanf("%i", &chooseReserve);
            system("cls");
        }
        while(chooseReserve > num_reserves);


        do
        {
            printf("=========================================\n");
            printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
            printf("=========================================\n\n");
            printf("| 1. ALTERAR DATA DA RESERVA\n");
            printf("| 2. ALTERAR TIPO DE QUARTO\n");
            printf("| 3. VOLTAR PARA O MENU\n\n");
            printf("| ESCOLHA UMA OPÇÃO: ");
            scanf("%i", &changeOption);
            system("cls");
        }
        while(changeOption != 1 && changeOption != 2 && changeOption != 3);


        switch(changeOption)
        {
        case 1:
            days = getDays(days);
            getCheckin(checkin);
            getCheckout(checkout);

            strcpy(reserves[chooseReserve - 1].checkin, checkin);
            strcpy(reserves[chooseReserve - 1].checkout, checkout);
            reserves[chooseReserve - 1].days = days;

            reserves[chooseReserve - 1].total = reserves[chooseReserve - 1].daily * days;

            printf("=========================================\n");
            printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
            printf("=========================================\n\n");
            printf("| RESERVA ALTERADA!");
            sleep(3);
            system("cls");
            GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
            break;
        case 2:
            room = roomOptions(room);

            switch(reserves[chooseReserve - 1].num_hotel)
            {
            case 1:
                switch(reserves[chooseReserve - 1].type_room)
                {
                case 1:
                    hotel01.rooms.suits.available++;
                    break;
                case 2:
                    hotel01.rooms.standard.available++;
                    break;
                case 3:
                    hotel01.rooms.deluxes.available++;
                    break;
                }
                break;
            case 2:
                switch(reserves[chooseReserve - 1].type_room)
                {
                case 1:
                    hotel02.rooms.suits.available++;
                    break;
                case 2:
                    hotel02.rooms.standard.available++;
                    break;
                case 3:
                    hotel02.rooms.deluxes.available++;
                    break;
                }
                break;
            case 3:
                switch(reserves[chooseReserve - 1].type_room)
                {
                case 1:
                    hotel03.rooms.suits.available++;
                    break;
                case 2:
                    hotel03.rooms.standard.available++;
                    break;
                case 3:
                    hotel03.rooms.deluxes.available++;
                    break;
                }
                break;
            }

            reserves[chooseReserve - 1].type_room = room;


            switch (reserves[chooseReserve - 1].num_hotel)
            {
            case 1:
                switch (room)
                {
                case 1:
                    hotel01.rooms.suits.available--;
                    break;
                case 2:
                    hotel01.rooms.standard.available--;
                    break;
                case 3:
                    hotel01.rooms.deluxes.available--;
                    break;
                }
                break;

            case 2:
                switch (room)
                {
                case 1:
                    hotel02.rooms.suits.available--;
                    break;
                case 2:
                    hotel02.rooms.standard.available--;
                    break;
                case 3:
                    hotel02.rooms.deluxes.available--;
                    break;
                }
                break;

            case 3:
                switch (room)
                {
                case 1:
                    hotel03.rooms.suits.available--;
                    break;
                case 2:
                    hotel03.rooms.standard.available--;
                    break;
                case 3:
                    hotel03.rooms.deluxes.available--;
                    break;
                }
                break;
            }


            switch(room)
            {
            case 1:
                reserves[chooseReserve - 1].daily = hotel01.rooms.suits.price;
                break;
            case 2:
                reserves[chooseReserve - 1].daily = hotel02.rooms.standard.price;
                break;
            case 3:
                reserves[chooseReserve - 1].daily = hotel03.rooms.deluxes.price;
                break;
            }

            reserves[chooseReserve - 1].total = reserves[chooseReserve - 1].daily *  reserves[chooseReserve - 1].days;


            printf("=========================================\n");
            printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
            printf("=========================================\n\n");
            printf("| RESERVA ALTERADA!");
            sleep(3);
            system("cls");
            GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
            break;
        case 3:
            system("cls");
            GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
            break;
        }

    }
    else
    {
        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("| AINDA NÃO HÁ RESERVAS!\n");
        sleep(3);
        system("cls");
        GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
    }
}

void deleteReservations()
{

    int reserveNumber;

    if(num_reserves > 0)
    {
        do
        {
            showReserves();
            printf("| DIGITE O NÚMERO DA RESERVA QUE DESEJA DELETAR: ");
            scanf("%i", &reserveNumber);
            system("cls");
        }
        while(reserveNumber > num_reserves);

        if(reserveNumber != 0)
        {

            int canceledHotel = reserves[reserveNumber - 1].num_hotel;
            int canceledRoomType = reserves[reserveNumber - 1].type_room;

            for (int i = reserveNumber - 1; i < num_reserves - 1; i++)
            {
                reserves[i] = reserves[i + 1];
            }

            num_reserves--;

            switch (canceledHotel)
            {
            case 1:
                switch (canceledRoomType)
                {
                case 1:
                    hotel01.rooms.suits.available++;
                    break;
                case 2:
                    hotel01.rooms.standard.available++;
                    break;
                case 3:
                    hotel01.rooms.deluxes.available++;
                    break;
                }
                break;

            case 2:
                switch (canceledRoomType)
                {
                case 1:
                    hotel02.rooms.suits.available++;
                    break;
                case 2:
                    hotel02.rooms.standard.available++;
                    break;
                case 3:
                    hotel02.rooms.deluxes.available++;
                    break;
                }
                break;

            case 3:
                switch (canceledRoomType)
                {
                case 1:
                    hotel03.rooms.suits.available++;
                    break;
                case 2:
                    hotel03.rooms.standard.available++;
                    break;
                case 3:
                    hotel03.rooms.deluxes.available++;
                    break;
                }
                break;
            }

            printf("=========================================\n");
            printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
            printf("=========================================\n\n");
            printf("| RESERVA CANCELADA!\n");
            sleep(3);
            system("cls");
            showOptionsGuests();
        }

    }
    else
    {
        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
        printf("=========================================\n\n");
        printf("| AINDA NÃO HÁ RESERVAS!\n");
        sleep(3);
        system("cls");
        showOptionsGuests();
    }
}

void listProperties() {
    printf("=========================================================\n");
    printf("   LISTA DE PROPRIEDADES E DISPONIBILIDADE DE QUARTOS\n");
    printf("=========================================================\n\n");

    printf("Hotel 01 - %s (%d estrelas)\n", hotel01.name, hotel01.stars);
    printf("Suíte: %d quartos disponíveis - Valor: R$%.2f\n", hotel01.rooms.suits.available, hotel01.rooms.suits.price);
    printf("Standard: %d quartos disponíveis - Valor: R$%.2f\n", hotel01.rooms.standard.available, hotel01.rooms.standard.price);
    printf("Deluxe: %d quartos disponíveis - Valor: R$%.2f\n\n", hotel01.rooms.deluxes.available, hotel01.rooms.deluxes.price);

    printf("Hotel 02 - %s (%d estrelas)\n", hotel02.name, hotel02.stars);
    printf("Suíte: %d quartos disponíveis - Valor: R$%.2f\n", hotel02.rooms.suits.available, hotel02.rooms.suits.price);
    printf("Standard: %d quartos disponíveis - Valor: R$%.2f\n", hotel02.rooms.standard.available, hotel02.rooms.standard.price);
    printf("Deluxe: %d quartos disponíveis - Valor: R$%.2f\n\n", hotel02.rooms.deluxes.available, hotel02.rooms.deluxes.price);

    printf("Hotel 03 -  %s (%d estrelas)\n", hotel03.name, hotel03.stars);
    printf("Suíte: %d quartos disponíveis - Valor: R$%.2f\n", hotel03.rooms.suits.available, hotel03.rooms.suits.price);
    printf("Standard: %d quartos disponíveis - Valor: R$%.2f\n", hotel03.rooms.standard.available, hotel03.rooms.standard.price);
    printf("Deluxe: %d quartos disponíveis - Valor: R$%.2f\n\n", hotel03.rooms.deluxes.available, hotel03.rooms.deluxes.price);

    printf("=========================================\n");
    printf("PRESSIONE ENTER PARA VOLTAR...");
    fflush(stdin);
    getchar();
    system("cls");
    GuestOrEmployee == 0 ? showOptionsEmployees() : showOptionsGuests();
}



int showOptionsGuests()
{
    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");
    printf("| 1. ADICIONAR RESERVA\n");
    printf("| 2. VISUALIZAR RESERVAS\n");
    printf("| 3. ALTERAR RESERVA\n");
    printf("| 4. CANCELAR RESERVA\n");
    printf("| 5. LISTAR PROPRIEDADES\n");
    printf("| 6. VOLTAR PARA O MENU\n\n");
    printf("| ESCOLHA UMA OPÇÃO: ");
    scanf("%i", &optionGuest);
    system("cls");


    switch(optionGuest)
    {
    case 1:
        addReserve(nameGuest);
        break;
    case 2:
        viewReservations();
        break;
    case 3:
        changeReservations();
        break;
    case 4:
        deleteReservations();
        break;
    case 5:
        listProperties();
        break;
    case 6:
        menu();
        break;
    }

    return 0;
}

int guests()
{
    GuestOrEmployee = 1;

    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");
    printf("SEJA BEM-VINDO!\n\n");
    printf("DIGITE SEU NOME: ");
    gets(nameGuest);
    system("cls");

    do
    {
        showOptionsGuests();
    }
    while(optionGuest != 1 && optionGuest != 2 && optionGuest != 3 && optionGuest != 4 && optionGuest != 5 && optionGuest != 6);

    return 0;
}


// FUNÇÃO PARA FINALIZAR O SISTEMA

void close()
{
    printf("=========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO HOTELEIRO   \n");
    printf("=========================================\n\n");
    printf("Finalizando o sistema...\n");
    sleep(3);
    system("cls");
    printf("Sistema finalizado!\n\n");
}
