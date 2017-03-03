
//Carregador de modelos 3D no formato OBJ
//Autor: Claudio Mota Oliveira
//Ultima modificação: 19/03/2016
//
#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

bool OBJ_COMENTAR_LEITURA = true;

struct Vertice{
    float x, y, z;
    Vertice(){
        x = y = z = 0.0f;
    }
    
    //Utilizados para leitura do arquivo:
    void ler(FILE* arquivo){
        fscanf(arquivo,"%f %f %f", &x, &y, &z);
    }
    
    void ler2(FILE* arquivo){
        fscanf(arquivo,"%f %f", &x, &y);
    }
};

struct Face{
    int vertices[3]; //Mapeamento dos vertices/normais/texturas
    int normais[3];
    int texturas[3];
    
    //Utilizado para leitura do arquivo:
    void ler(FILE* arquivo){
        int i;
        char aux;
        
        for(i = 0; i < 3; i++){
            vertices[i] = texturas[i] = normais[i] = -1;
            fscanf(arquivo, "%i", vertices+i);
            vertices[i]--;
            fscanf(arquivo, "%c", &aux);
            if(aux == '/'){
                fscanf(arquivo, "%i", texturas+i);
                texturas[i]--;
                fscanf(arquivo, "%c", &aux);
                if(aux == '/'){
                    fscanf(arquivo, "%i", normais+i);
                    normais[i]--;
                }
            }
        }
    }
};

//Grupos isolados do objeto, podendo possuir sua própria textura
struct GrupoVertices{
    int numeroFaces;
    Face* faces;
    GLuint textura;
    unsigned char* imagem;
    
    GrupoVertices(){
        textura = 0;
        imagem = NULL;
        numeroFaces = 0;
        faces = NULL;
    }
    
    static unsigned char* carregarBMP(char* nome, int* retLarg, int* retAlt){
        FILE* arquivo = fopen(nome, "rb");
        if(!arquivo) return NULL;
        unsigned char* retBytes = NULL;
        *retLarg = 0;
        *retAlt = 0;
        int i,j,tamanho, reservado,offset,infosize;
        int compressao, imgSize,pixelPerMX,pixelPerMY,coresUsadas,coresImportantes;
        short bitCount,planes;
        fread(&bitCount, 2, 1, arquivo);
        fread(&tamanho, 4, 1, arquivo);
        fread(&reservado, 4, 1, arquivo);
        fread(&offset, 4, 1, arquivo);
        fread(&infosize, 4, 1, arquivo);
        fread(retLarg, 4, 1, arquivo);
        fread(retAlt, 4, 1, arquivo);
        fread(&planes, 2, 1, arquivo);
        fread(&bitCount, 2, 1, arquivo);
        if(bitCount != 24){
            return NULL;
        }
        fread(&compressao, 4, 1, arquivo);
        fread(&imgSize, 4, 1, arquivo);
        fread(&pixelPerMX, 4, 1, arquivo);
        fread(&pixelPerMY, 4, 1, arquivo);
        fread(&coresUsadas, 4, 1, arquivo);
        fread(&coresImportantes, 4, 1, arquivo);
        imgSize = (*retAlt)*(*retLarg)*4;
        retBytes = new unsigned char[imgSize];
        for(i = 0; i < *retAlt; i++){
            int numeroAuxiliar;
            
            for(j = 0; j < (*retLarg); j++){
                retBytes[(i*(*retLarg)+j)*4+2] = (unsigned char)fgetc(arquivo);
                retBytes[(i*(*retLarg)+j)*4+1] = (unsigned char)fgetc(arquivo);
                retBytes[(i*(*retLarg)+j)*4] = (unsigned char)fgetc(arquivo);
                retBytes[(i*(*retLarg)+j)*4+3] = 255;
            }
            if((*retLarg)%4) fread(&numeroAuxiliar,1,(*retLarg)%4,arquivo);
        }
        fclose(arquivo);
        return retBytes;
    }
    
    void setTextura(char* nome){
        int largura;
        int altura;
        int pix;
        
        //imagem = stbi_load(nome, &largura, &altura, &pix,3);
        imagem = carregarBMP(nome, &largura, &altura);
        
        if(!imagem) return;
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1,&textura);
        glBindTexture(GL_TEXTURE_2D,textura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,largura,altura,0,GL_RGBA,GL_UNSIGNED_BYTE,imagem);
    }
    
    ~GrupoVertices(){
        if(textura) glDeleteTextures(1,&textura);
        if(faces) delete [] faces;
        if(imagem) delete [] imagem;
    }
};

//Estrutura principal para criação dos objetos 3D
struct Modelo{
    int numeroGrupos;
    GrupoVertices* grupos;  //Partes do objeto
    int numeroVertices;
    Vertice* vertices;
    int numeroNormais;
    Vertice* normais;
    int numeroTexturas;
    Vertice* texturas;
    
    //Construtor---------------------------------------------------------------
    Modelo(){
        numeroGrupos = numeroVertices = numeroTexturas = numeroNormais = 0;
        vertices = NULL;
        texturas = NULL;
        normais = NULL;
        grupos = NULL;
    }
    
    //Desenha o objeto utilizando ponto a ponto (pode ser melhorado)-----------
    void desenhar(){
        int i, g, f;
        for(g = 0; g < numeroGrupos; g++){
            if(grupos[g].textura){
                glBindTexture(GL_TEXTURE_2D, grupos[g].textura);
            }
            glBegin(GL_TRIANGLES);
            for(f = 0; f < grupos[g].numeroFaces; f++){
                for(i = 0; i < 3; i++){
                    if(grupos[g].faces[f].texturas[i] >= 0)
                        glTexCoord2f(texturas[grupos[g].faces[f].texturas[i]].x,
                                     texturas[grupos[g].faces[f].texturas[i]].y);
                    if(grupos[g].faces[f].normais[i] >= 0)
                        glNormal3f(normais[grupos[g].faces[f].normais[i]].x,
                                   normais[grupos[g].faces[f].normais[i]].y,
                                   normais[grupos[g].faces[f].normais[i]].z);
                    glVertex3f(vertices[grupos[g].faces[f].vertices[i]].x,
                               vertices[grupos[g].faces[f].vertices[i]].y,
                               vertices[grupos[g].faces[f].vertices[i]].z);
                }
            }
            glEnd();
        }
    }
    //Desenha o objeto utilizando ponto a ponto (pode ser melhorado)-----------
    void desenharTextura(){
        int i, g, f;
        for(g = 0; g < numeroGrupos; g++){
            if(grupos[g].textura){
                glBindTexture(GL_TEXTURE_2D, grupos[g].textura);
                glBegin(GL_TRIANGLES);
                
                glNormal3f(0,0,-1);
                glTexCoord2f(0,0);
                glVertex3f(-1, -1, 0);
                glTexCoord2f(1,0);
                glVertex3f(1, -1, 0);
                glTexCoord2f(1,1);
                glVertex3f(1, 1, 0);
                glTexCoord2f(0,0);
                glVertex3f(-1, -1, 0);
                glTexCoord2f(0,1);
                glVertex3f(-1, 1, 0);
                glTexCoord2f(1,1);
                glVertex3f(1, 1, 0);
                glEnd();
                break;
            }
        }
    }
    //Desenha linhas das faces do objeto---------------------------------------
    void desenharLinhas(){
        int i, g, f;
        glBegin(GL_LINES);
        for(g = 0; g < numeroGrupos; g++){
            for(f = 0; f < grupos[g].numeroFaces; f++){
                for(i = 1; i < 3; i++){
                    glVertex3f(vertices[grupos[g].faces[f].vertices[i-1]].x,
                               vertices[grupos[g].faces[f].vertices[i-1]].y,
                               vertices[grupos[g].faces[f].vertices[i-1]].z);
                    glVertex3f(vertices[grupos[g].faces[f].vertices[i]].x,
                               vertices[grupos[g].faces[f].vertices[i]].y,
                               vertices[grupos[g].faces[f].vertices[i]].z);
                }
            }
        }
        glEnd();
    }
    
    //Carrega o objeto---------------------------------------------------------
    static Modelo* carregarObj(char* nomeArquivo, bool automatico = true){
        Modelo* retorno = NULL;
        FILE* arquivo = fopen(nomeArquivo, "r");
        char aux;
        int v,f,t,n,g;
        int numV, numT, numN, numG;
        int texTam;
        char* texto = new char[1000];
        int* facePorGrupo = new int[1000];
        memset(facePorGrupo, 0, sizeof(int)*1000);
        numV = numT = numN = 0;
        numG = 1;
        if(arquivo){
            //Primeira passada------------------------------------
            fseek(arquivo, 0, SEEK_SET);
            while(fscanf(arquivo,"%c", &aux) != EOF){
                switch(aux){
                    case 'o':
                        numG++;
                        break;
                    case 'g':
                        numG++;
                        break;
                    case 'v':
                        fscanf(arquivo,"%c", &aux);
                        switch(aux){
                            case 't':
                                numT++;
                                break;
                            case 'n':
                                numN++;
                                break;
                            default:
                                numV++;
                                break;
                        }
                        break;
                    case 'f':
                        facePorGrupo[numG-1]++;
                        break;
                }
                if(aux != 10) fgets(texto, 1000, arquivo);
            }
            
            retorno = new Modelo();
            retorno->numeroGrupos = numG;
            retorno->grupos = new GrupoVertices[numG];
            retorno->numeroVertices = numV;
            retorno->vertices = new Vertice[numV];
            retorno->numeroTexturas = numT;
            retorno->texturas = new Vertice[numT];
            retorno->numeroNormais = numN;
            retorno->normais = new Vertice[numN];
            
            if(OBJ_COMENTAR_LEITURA){
                printf("//-carregando %s ----//\n", nomeArquivo);
                printf("numero de vertices do modelo: %i\n", numV);//numero de vertices e outras coisas
                printf("Partes do modelo:\nParte[0] (global) possuindo %i faces\n", facePorGrupo[0]);
            }
            for(g = 0; g < numG; g++){
                retorno->grupos[g].numeroFaces = facePorGrupo[g];
                retorno->grupos[g].faces = new Face[facePorGrupo[g]];
            }
            
            v = f = t = n = g = 0;
            //Segunda passada-----------------------------------
            fseek(arquivo, 0, SEEK_SET);
            while(fscanf(arquivo,"%c", &aux) != EOF){
                switch(aux){
                    case '#':
                        fgets(texto, 1000, arquivo);
                        //printf("%s\n",texto); //comentarios do arquivo
                        break;
                    case 'o':
                        g++;
                        f = 0;
                        fgets(texto, 1000, arquivo);
                        if(strlen(texto) > 0) texto[strlen(texto)-1] = 0;
                        if(OBJ_COMENTAR_LEITURA) printf("Parte[%i] (%s) possuindo %i faces\n", g, texto, facePorGrupo[g]);
                        break;
                    case 'g':
                        g++;
                        f = 0;
                        fgets(texto, 1000, arquivo);
                        if(strlen(texto) > 0) texto[strlen(texto)-1] = 0;
                        if(OBJ_COMENTAR_LEITURA) printf("Parte[%i] (%s) possuindo %i faces\n", g, texto, facePorGrupo[g]);
                        break;
                    case 'u':
                        fscanf(arquivo,"%s", texto);
                        if(!strcmp(texto, "semtl") && automatico){
                            fscanf(arquivo,"%s", texto);
                            texTam = strlen(texto);
                            texto[texTam] = '.';
                            texto[texTam+1] = 'b';
                            texto[texTam+2] = 'm';
                            texto[texTam+3] = 'p';
                            texto[texTam+4] = '\0';
                            retorno->grupos[g].setTextura(texto);
                        }else{
                            fgets(texto, 1000, arquivo);
                        }
                        break;
                    case 'v':
                        fscanf(arquivo,"%c", &aux);
                        switch(aux){
                            case 't':
                                retorno->texturas[t].ler2(arquivo);
                                t++;
                                break;
                            case 'n':
                                retorno->normais[n].ler(arquivo);
                                n++;
                                break;
                            default:
                                retorno->vertices[v].ler(arquivo);
                                v++;
                                break;
                        }
                        break;
                    case 'f':
                        retorno->grupos[g].faces[f].ler(arquivo);
                        f++;
                        break;
                    default:
                        if(aux != 10) fgets(texto, 1000, arquivo);
                        break;
                }
            }
            //------------------------------------------
            if(OBJ_COMENTAR_LEITURA) printf("\n");
            fclose(arquivo);
        }
        
        delete [] texto;
        delete [] facePorGrupo;
        
        if(!retorno && OBJ_COMENTAR_LEITURA) printf("Nao foi possivel abrir o arquivo (%s).\n", nomeArquivo);
        
        return retorno;
    }
    
    static Modelo* carregarObj(char* nomeArquivo, char* nomeTexturaBMP){
        Modelo* retorno = carregarObj(nomeArquivo,false);
        if(retorno){
            retorno->grupos[0].setTextura(nomeTexturaBMP);
        }
        return retorno;
    }
    
    static Modelo* carregarObj(char* nomeArquivo, char** nomesTexturasBMP){
        int g;
        Modelo* retorno = carregarObj(nomeArquivo,false);
        if(retorno)
            for(g = 0; g < retorno->numeroGrupos; g++){
                if(nomesTexturasBMP[g]) retorno->grupos[g].setTextura(nomesTexturasBMP[g]);
            }
        return retorno;
    }
    //Deleta o objeto----------------------------------------------------------
    ~Modelo(){
        if(vertices) delete [] vertices;
        if(texturas) delete [] texturas;
        if(normais) delete [] normais;
        if(grupos) delete [] grupos;
    }
};
