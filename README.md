# Tp_Se
#Adjou maroua g3 
#Q1 : Quelles sont les structures de données à utiliser ?
-Matrices B, C, et A : Utilisez des tableaux bidimensionnels pour stocker les matrices B, C et A.
-Buffer buffer :
 Utilisez un tableau  qui stocker les résultats intermédiaires.
#Q2: Comment allez-vous protéger l'accès à ces données?
-Sémaphores :
empty,full,mutex, pour contrôler l'accès au buffer . emptyreprésente le nombre d'emplacements vides dans le tampon, et fullreprésente le nombre d'emplacements occupés.
Utilisez un mutex pour protéger l'accès aux matrices B, C, et A si plusieurs threads doivent les modifier simultanément.
#Q3: Quels sont les risques?
-Blocage  : Assurez-vous d'éviter les situations de blocage en utilisant les sémaphores et les mutex de manière appropriée.
-Optimisez la conception pour minimiser les temps d'attente et maximiser l'utilisation des ressources du processeur.
-Dépassement Buffer : Il est important de gérer correctement la taille du buffer(N) pour éviter les dépassements de tampon.
