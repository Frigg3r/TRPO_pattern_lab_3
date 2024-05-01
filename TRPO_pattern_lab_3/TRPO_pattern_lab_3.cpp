#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс для ингредиентов
class Ingredient {
public:
    Ingredient(const string& name, double calories_per_100g, double amount)
        : name_(name), calories_per_100g_(calories_per_100g), amount_(amount) {}

    virtual ~Ingredient() {}

    const string& getName() const {
        return name_;
    }

    double getAmount() const {
        return amount_;
    }

    // Метод для подсчета калорий
    virtual double calculateCalories() const {
        return (calories_per_100g_ / 100.0) * amount_;
    }

private:
    string name_;
    double calories_per_100g_;
    double amount_;
};

// Посетитель - интерфейс операций
class Visitor {
public:
    virtual void visit(const Ingredient& ingredient) const = 0;
    virtual ~Visitor() {}
};

// Класс рецепта блюда
class Recipe {
public:
    void addIngredient(const Ingredient& ingredient) {
        ingredients.push_back(ingredient);
    }

    void accept(const Visitor& visitor) const {
        for (const Ingredient& ingredient : ingredients) {
            visitor.visit(ingredient);
        }
    }

private:
    vector<Ingredient> ingredients;
};

// Конкретные продукты
class Potato : public Ingredient {
public:
    Potato(double amount) : Ingredient("Potato", 77.0, amount) {}
};

class Beet : public Ingredient {
public:
    Beet(double amount) : Ingredient("Beet", 43.0, amount) {}
};

class Onion : public Ingredient {
public:
    Onion(double amount) : Ingredient("Onion", 40.0, amount) {}
};

class Mayonnaise : public Ingredient {
public:
    Mayonnaise(double amount) : Ingredient("Mayonnaise", 680.0, amount) {}
};

class Fish : public Ingredient {
public:
    Fish(double amount) : Ingredient("Fish", 170.0, amount) {}
};

// Конкретный посетитель для вывода информации о рецепте
class RecipeVisitor : public Visitor {
public:
    void visit(const Ingredient& ingredient) const override {
        cout << ingredient.getName() << ": " << ingredient.getAmount() << " g" << endl;
    }
};

// Конкретный посетитель для подсчета калорий рецепта
class RecipeCaloriesVisitor : public Visitor {
public:
    RecipeCaloriesVisitor() : total_calories_(0.0) {}

    void visit(const Ingredient& ingredient) const override {
        total_calories_ += ingredient.calculateCalories();
    }

    double getTotalCalories() const {
        return total_calories_;
    }

private:
    mutable double total_calories_;
};

int main() {
    Recipe recipe;
    recipe.addIngredient(Potato(200.0));
    recipe.addIngredient(Beet(150.0));
    recipe.addIngredient(Onion(100.0));
    recipe.addIngredient(Mayonnaise(50.0));
    recipe.addIngredient(Fish(300.0));

    RecipeVisitor recipeVisitor;
    recipe.accept(recipeVisitor);

    RecipeCaloriesVisitor caloriesVisitor;
    recipe.accept(caloriesVisitor);
    double total_calories = caloriesVisitor.getTotalCalories();
    cout << "Total calories: " << total_calories << endl;

    return 0;
}
