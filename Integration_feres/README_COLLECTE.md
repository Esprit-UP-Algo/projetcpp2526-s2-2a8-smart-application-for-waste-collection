# 📦 PROJET COLLECTE - Modules Recyclage et Conteneurs

## 🎯 Description

Application Qt C++ pour la gestion des opérations de recyclage et des conteneurs intelligents.

---

## 📁 Fichiers inclus

```
collecte/
├── main.cpp                    # Point d'entrée
├── mainwindow.h                # Déclarations et structures
├── mainwindow.cpp              # Implémentation (953 lignes)
├── mainwindow.ui               # Interface graphique Qt
├── collecte.pro                # Configuration Qt Project
└── GUIDE_UTILISATION.md        # Documentation complète
```

---

## ⚡ Démarrage rapide

### 1. Copier les fichiers
Copiez tous les fichiers dans un dossier "collecte"

### 2. Ouvrir dans Qt Creator
```
File → Open File or Project → Sélectionnez "collecte.pro"
```

### 3. Compiler et exécuter
```
Build → Rebuild All
Run (Ctrl + R)
```

---

## ✨ Fonctionnalités

### Module Recyclage ♻️
- Gestion des opérations de recyclage
- Suivi des matériaux (Plastique, Carton, Verre, etc.)
- Calcul automatique des taux de recyclage
- Ajout/Suppression d'opérations
- Tableaux détaillés

### Module Conteneurs 🗑️
- Gestion des conteneurs intelligents
- Localisation GPS (latitude/longitude)
- Monitoring du remplissage (0-100%)
- Suivi de la température
- État et maintenance
- Ajout/Suppression de conteneurs

---

## 🎨 Captures d'écran

### Tableau Recyclage
```
┌────┬──────────────┬──────────┬─────────────┬────────────┬────────┐
│ ID │ Matériau     │ Entrée   │ Recyclée    │ Rejetée    │ Taux % │
├────┼──────────────┼──────────┼─────────────┼────────────┼────────┤
│ 1  │ Plastique PET│ 500.0 kg │ 450.0 kg    │ 50.0 kg    │ 90.0   │
│ 2  │ Carton       │ 800.0 kg │ 720.0 kg    │ 80.0 kg    │ 90.0   │
│ 3  │ Verre        │ 300.0 kg │ 285.0 kg    │ 15.0 kg    │ 95.0   │
└────┴──────────────┴──────────┴─────────────┴────────────┴────────┘
```

---

## 🔧 Technologies utilisées

- **Qt 6.x** - Framework GUI
- **C++17** - Langage de programmation
- **Qt Widgets** - Interface graphique
- **Qt Designer** - Design visuel

---

## 📚 Documentation

Consultez **GUIDE_UTILISATION.md** pour :
- Instructions détaillées
- Guide d'intégration dans un autre projet
- Personnalisation
- Dépannage

---

## ✅ État des fonctionnalités

| Fonctionnalité | Recyclage | Conteneurs |
|----------------|-----------|------------|
| Affichage tableau | ✅ | ✅ |
| Données d'exemple | ✅ | ✅ |
| Ajouter | ✅ | ✅ |
| Modifier | ⚠️ | ⚠️ |
| Supprimer | ⚠️ | ✅ |
| Rechercher | ⚠️ | ⚠️ |
| Exporter PDF | ⚠️ | ⚠️ |
| Statistiques | ⚠️ | ⚠️ |

**Légende** :
- ✅ Fonctionnel
- ⚠️ À implémenter (QMessageBox temporaire)

---

## 🚀 Utilisation standalone

```bash
# 1. Créer le dossier
mkdir collecte
cd collecte

# 2. Copier les 5 fichiers fournis

# 3. Ouvrir dans Qt Creator
qtcreator collecte.pro

# 4. Compiler
# Build → Rebuild All

# 5. Exécuter
# Run
```

---

## 🔗 Intégration dans un projet existant

Si vous voulez intégrer ces modules dans votre projet "waste" :

1. Ajoutez les fichiers mainwindow.* à votre projet
2. Modifiez waste.pro pour inclure ces fichiers
3. Créez une fonction pour ouvrir MainWindow depuis waste

Exemple :
```cpp
void Waste::on_pushButton_recyclage_acc_clicked()
{
    MainWindow *fenetre = new MainWindow();
    fenetre->setAttribute(Qt::WA_DeleteOnClose);
    fenetre->show();
}
```

Voir **GUIDE_UTILISATION.md** pour les détails complets.

---

## 📊 Structures de données

### RecyclageData
```cpp
struct RecyclageData {
    int id;
    QString materiau;
    double qteEntree;
    double qteRecyclee;
    double qteRejetee;
    double taux;
    QString destination;
    double valeur;
};
```

### ConteneurData
```cpp
struct ConteneurData {
    int id;
    QString capacite;
    QString localisation;
    QString adresseComplete;
    double latitude;
    double longitude;
    QString typePropriete;
    int niveauRemplissage;
    double temperature;
    QString etatConteneur;
    QString dateDerniereCollecte;
    QString typesDechet;
};
```

---

## 🎨 Design

- Palette de couleurs : Bleu marine professionnel
- Gradients modernes
- Tableaux stylisés
- Formulaires élégants
- Boutons avec effets hover

---

## 🐛 Dépannage

### Erreur de compilation
```
Solution : Build → Clean All → Rebuild All
```

### Tableau vide
```
Solution : Vérifiez que chargerDonneesExemplesRecyclage() 
          est appelée dans le constructeur
```

### Bouton ne fonctionne pas
```
Solution : Vérifiez le nom du bouton dans l'UI
          Doit correspondre au slot (on_nomBouton_clicked)
```

---

## 📞 Support

Pour plus d'aide, consultez :
1. **GUIDE_UTILISATION.md** - Documentation détaillée
2. Messages d'erreur du compilateur
3. Documentation Qt : https://doc.qt.io/

---

## 📝 Licence

Projet éducatif - Libre d'utilisation

---

## 👥 Auteur

Projet WasteFlow SMART - Module Collecte

---

**Version 1.0** - Prêt à l'emploi ✅

Bon développement ! 🚀
