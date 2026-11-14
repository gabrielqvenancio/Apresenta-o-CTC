/**
 * @file JogoRPG.hpp
 * @brief Entidades e mecânicas de combate do RPG.
 */

#ifndef JOGO_RPG_HPP
#define JOGO_RPG_HPP

#include <string>
#include <vector>

/**
 * @namespace RPG
 * @brief Encapsula as mecânicas principais do jogo.
 */
namespace RPG {

/**
 * @brief Equipamento ofensivo que pode ser empunhado.
 */
class Arma {
public:
    /**
     * @brief Inicializa os atributos da arma.
     * @param nome Nome exibido na interface.
     * @param danoBase Dano físico bruto antes de modificadores.
     */
    Arma(std::string nome, int danoBase);

    /**
     * @brief Calcula o dano final considerando chance de acerto crítico.
     * @return Valor total de dano a ser aplicado.
     */
    int calcularDano() const;

private:
    std::string nome;
    int danoBase;
};

/**
 * @brief Contêiner de itens com limite de capacidade.
 * @tparam T Tipo de item armazenado.
 */
template <typename T>
class Inventario {
public:
    /**
     * @brief Guarda um item na mochila.
     * @param item Objeto a ser armazenado.
     * @pre O inventário não pode ter atingido a capacidade máxima.
     */
    void adicionar(const T& item);

private:
    std::vector<T> itens;
};

/**
 * @brief Qualquer ser vivo ou interativo no mundo do jogo.
 */
class Entidade {
public:
    /**
     * @brief Inicializa uma entidade no mapa.
     * @param nome Nome de exibição.
     * @param vidaMaxima Pontos de vida iniciais e limite máximo de cura.
     */
    Entidade(std::string nome, int vidaMaxima);
    virtual ~Entidade() = default;

    /**
     * @brief Executa o ataque padrão.
     * @param alvo Entidade que receberá o impacto.
     */
    virtual void atacar(Entidade& alvo) = 0;

    /**
     * @brief Subtrai pontos de vida.
     * @param quantidade Valor de dano sofrido.
     * @post Marca a entidade como derrotada se a vida chegar a zero.
     */
    void receberDano(int quantidade);

protected:
    std::string nome;
    int vidaAtual;
};

/**
 * @brief Personagem jogável focado em combate corpo a corpo.
 */
class Guerreiro : public Entidade {
public:
    /**
     * @brief Cria um novo guerreiro.
     * @param nome Nome do herói.
     * @param forca Multiplicador aplicado ao dano físico.
     */
    Guerreiro(std::string nome, int forca);

    /**
     * @brief Define a arma ativa na mão principal.
     * @param novaArma Arma escolhida, ou `nullptr` para desarmar.
     */
    void equiparArma(Arma* novaArma);

    /**
     * @brief Soma a força do guerreiro ao dano da arma equipada.
     * @param alvo Entidade que receberá o golpe.
     */
    void atacar(Entidade& alvo) override;

private:
    int forca;
    Arma* armaEquipada = nullptr;
    Inventario<std::string> mochila;
};

/**
 * @brief Inimigo chefe com ataques elementais em área.
 */
class Dragao : public Entidade {
public:
    /**
     * @brief Invoca um dragão.
     * @param nome Título do chefe.
     * @param poderFogo Dano elemental adicional.
     */
    Dragao(std::string nome, int poderFogo);

    /**
     * @brief Executa um sopro flamejante que ignora armadura física.
     * @param alvo Entidade atingida pelas chamas.
     */
    void atacar(Entidade& alvo) override;

private:
    int poderFogo;
};

} // namespace RPG

#endif // JOGO_RPG_HPP
