import java.util.Scanner;
import java.io.*;

class game {
    //atributos da classe
    private int appID;
    private String name;
    private String releaseDate;
    private int estimatedOwners;
    private float price;
    private String supportedLanguages[];
    private int metacriticScore;
    private float userScore;
    private int achievements;
    private String publishers[];
    private String developers[];
    private String categories[];
    private String genres[];
    private String tags[];

    //metodo set
    public void setGame(int appID, String name, String releaseDate, int estimatedOwners, float price, String supportedLanguages[], int metacriticScore, int userScore, int achievements, String publishers[], String developers[], String categories[], String genres[],String tags[]){
        this.appID = appID;
        this.name = name;
        this.releaseDate = formatarData(releaseDate);
        this.estimatedOwners = estimatedOwners;
        this.price = price;
        this.supportedLanguages = supportedLanguages;
        this.metacriticScore = metacriticScore;
        this.userScore = userScore;
        this.achievements = achievements;
        this.publishers = publishers;
        this.developers = developers;
        this.categories = categories;
        this.genres = genres;
        this.tags = tags;
    };

    // Métodos set individuais
    public void setAppID(String appID){
        this.appID = Integer.parseInt(appID);
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setReleaseDate(String releaseDate) {
        this.releaseDate = formatarData(releaseDate);
    }
    public void setEstimatedOwners(String estimatedOwners) {
        String aux = "";
        for(int i = 0; i < estimatedOwners.length(); i++) {
            if(estimatedOwners.charAt(i) >= '0' && estimatedOwners.charAt(i) <= '9') {
                aux += estimatedOwners.charAt(i);
            }
        }
        this.estimatedOwners = Integer.parseInt(aux);
    }
    public void setPrice(String price) {
        this.price = Float.parseFloat(price);
    }
    public void setSupportedLanguages(String supportedLanguages) {
        this.supportedLanguages = formatarArrayString(supportedLanguages, 0);
    }
    public void setMetacriticScore(String metacriticScore) {
        if(metacriticScore == null || metacriticScore.isEmpty()) {
            this.metacriticScore = -1;
        } else {
            this.metacriticScore = Integer.parseInt(metacriticScore);
        }
    }
    public void setUserScore(String userScore) {
        if(userScore == null || userScore.isEmpty() || userScore.equals("tbd")) {
            this.userScore = -1;
        } else {
            this.userScore = (int)(Float.parseFloat(userScore) * 10);
        }
    }
    public void setAchievements(String achievements) {
        if(achievements == null || achievements.isEmpty()) {
            this.achievements = 0;
        } else {
            this.achievements = Integer.parseInt(achievements);
        } 
    }
    public void setPublishers(String publishers) {
        this.publishers = removerEspacosIniciais(formatarArrayString(publishers, 0));
    }
    public void setDevelopers(String developers) {
        this.developers = removerEspacosIniciais(formatarArrayString(developers, 0));
    }
    public void setCategories(String categories) {
        this.categories = formatarArrayString(categories, 0);
    }
    public void setGenres(String genres) {
        this.genres = formatarArrayString(genres, 1);
    }
    public void setTags(String tags) {
        this.tags = formatarArrayString(tags, 1);
    }

    //metodos get
    public int getAppID(){return appID;}
    public String getName(){return name;}
    public String getReleaseDate(){return releaseDate;}
    public int getEstimatedOwners(){return estimatedOwners;}
    public float getPrice(){return price;}
    public String[] getSupportedLanguages(){return supportedLanguages;}
    public int getMetacriticScore(){return metacriticScore;}
    public float getUserScore(){return userScore;}
    public int getAchievements(){return achievements;}
    public String[] getPublishers(){return publishers;}
    public String[] getDevelopers(){return developers;}
    public String[] getCategories(){return categories;}
    public String[] getGenres(){return genres;}
    public String[] getTags(){return tags;}

    //prepara o pub out
    public String pubOut(){
        return "=> " + appID + " ## " + name + " ## " + releaseDate + " ## " + estimatedOwners + " ## " + (price == 0.00f ? "0.0" : String.format("%.2f", price).replaceAll("0$", "").replace(',', '.')) +
        " ## " + formatarLinguas(supportedLanguages) + " ## " + metacriticScore + " ## " + userScore + " ## " + achievements + " ## " + formatarArray(publishers) + " ## " 
        + formatarArray(developers) + " ## " + formatarArray(categories) + " ## " + formatarArray(genres) + " ## " + formatarArray(tags) + " ##";
    }

    //formata os arrays para o print
    private String formatarArray(String[] array) {
        return (array == null || array.length == 0) ? "[]" : "[" + String.join(", ", array) + "]";
    }

    private String formatarLinguas(String[] array){
        return (array == null || array.length == 0) ? "[]" : "[" + String.join(",", array) + "]";
    }

    //formata a data de lançamento para o print
    private String formatarData(String data){
        String mes = "", dia = "", ano = "", dataFormatada = "";
        for(int i = 0; i < 3; i++) {
            mes += data.charAt(i);
        }
        if(data.charAt(5) == ',') {
            dia += "0";
            dia += data.charAt(4);
            for(int i = 7; i < data.length(); i++) {
                ano += data.charAt(i);
            }
        }
        else {
            dia += data.charAt(4);
            dia += data.charAt(5);
            for(int i = 8; i < data.length(); i++) {
                ano += data.charAt(i);
            }
        }
        switch(mes) {
            case "Jan": mes = "01"; break;
            case "Feb": mes = "02"; break;
            case "Mar": mes = "03"; break;
            case "Apr": mes = "04"; break;
            case "May": mes = "05"; break;
            case "Jun": mes = "06"; break;
            case "Jul": mes = "07"; break;
            case "Aug": mes = "08"; break;
            case "Sep": mes = "09"; break;
            case "Oct": mes = "10"; break;
            case "Nov": mes = "11"; break;
            case "Dec": mes = "12"; break;
            default: mes = "01"; break;     
        }
        dataFormatada = dia + "/" + mes + "/" + ano;
        return dataFormatada;
    }

    // Funções auxiliares do código de exemplo
    public String[] removerEspacosIniciais(String[] array) {
        if (array == null) {
            return null;
        }
        
        String[] resultado = new String[array.length];
        
        for (int i = 0; i < array.length; i++) {
            if (array[i] != null) {
                resultado[i] = array[i].replaceFirst("^\\s+", "");
            } else {
                resultado[i] = null;
            }
        }
        
        return resultado;
    }

    public String[] formatarArrayString(String entrada, int tipo) {
        int virgulas = 0;
        for(int i = 0; i < entrada.length(); i++) {
            char c = entrada.charAt(i);
            if(c == ',') {
                virgulas++;
            }
        }
        String resp[] = new String[virgulas + 1];
        String aux = "";
        int contador = 0;
        if(tipo == 1){
            for(int i = 0; i < entrada.length(); i++) {
                char c = entrada.charAt(i); 
                if(c == ',') {
                    resp[contador] = aux;
                    contador++;
                    aux = "";
                }
                else {
                    if(!(c == '[' || c == ']')) {
                        aux += c;
                    } 
                }
            }
        }else{
            for(int i = 0; i < entrada.length(); i++) {
                char c = entrada.charAt(i); 
                if(c == ',') {
                    resp[contador] = aux;
                    contador++;
                    aux = "";
                }
                else {
                    if(!(c == '[' || c == ']' || c == '\'')) {
                        aux += c;
                    } 
                }
            }
        }
        resp[contador] = aux;
        return resp;
    }
}

public class main {
    public static boolean compare(String str1, String str2) {
        boolean resposta = true;

        if (str1.length() != str2.length()) {
                resposta = false;
            }else{
            boolean diferente = false;
            int i = 0;
                while (i < str1.length() && !diferente) {
                    if (str1.charAt(i) != str2.charAt(i)) {
                            diferente = true;
                    resposta = false;
                    }
            i++;
                }
        }
        return resposta;
    }

    public static void sets(game game, String array[]){
        game.setAppID(array[0]);
        game.setName(array[1]);
        game.setReleaseDate(array[2]);
        game.setEstimatedOwners(array[3]);
        game.setPrice(array[4]);
        game.setSupportedLanguages(array[5]);
        game.setMetacriticScore(array[6]);
        game.setUserScore(array[7]);
        game.setAchievements(array[8]);
        game.setPublishers(array[9]);
        game.setDevelopers(array[10]);
        game.setCategories(array[11]);
        game.setGenres(array[12]);
        game.setTags(array[13]);
    }

    public static void main(String[] args) throws FileNotFoundException{
        //cria o scanner para o arquivo
        Scanner scanner = new Scanner(System.in);
        File arq = new File("/tmp/games.csv");
        Scanner scannerArq = new Scanner(arq);

        game dados[] = new game[2000];
        int numGames = 0;

        // Pular o cabeçalho
        if (scannerArq.hasNextLine()) {
            scannerArq.nextLine();
        }

        // Ler o arquivo CSV
        while(scannerArq.hasNextLine()) {
            String entrada = scannerArq.nextLine();
            String array[] = new String[14]; 
            String aux = "";
            int contador = 0;
            boolean aspas = false;

            for(int i = 0; i < entrada.length(); i++){
                char c = entrada.charAt(i);

                if(c == '"'){
                    aspas = !aspas;
                } else if(c == ',' && !aspas){
                    array[contador] = aux;
                    contador++;
                    aux = "";
                } else {
                    aux = aux + c;
                }
            }

            array[contador] = aux;

            // Criar objeto game e configurar atributos
            dados[numGames] = new game();
            sets(dados[numGames], array);
            numGames++;
        }

        // Processar entradas do usuário
        String flag = "FIM";
        boolean continuar = true;
        
        while (continuar) {
            String busca = scanner.nextLine();

            if (compare(busca, flag)) {
                continuar = false;
            } else {
                int idBusca = Integer.parseInt(busca);
                boolean encontrado = false;
                
                for(int i = 0; i < numGames; i++) {
                    if(idBusca == dados[i].getAppID()) {
                        System.out.println(dados[i].pubOut());
                        encontrado = true;
                        break;
                    }
                }
                
                if (!encontrado) {
                    System.out.println("Game não encontrado");
                }
            }
        }

        scanner.close();
        scannerArq.close();
    }

}
