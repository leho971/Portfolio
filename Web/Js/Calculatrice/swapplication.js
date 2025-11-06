const versionapplication='v0.0.1';

self.addEventListener('install', function(event) {
  event.waitUntil(
    caches.open(versionapplication).then(function(cache) {
      return cache.addAll([
        '/',
        '/index.html',
        '/bootstrap.min.css',
        '/application.css',
        '/bootstrap.min.js',
        '/application.js',
        '/swapplication.js',
        '/application.txt',
        '/application_144.png',
        '/application_512.png'
      ]);
    })
  );
});

// on ecoute les requetes serveurs
self.addEventListener('fetch', function(event) {
  var cachedResponse = caches.match(event.request)
  // La donnée est disponible en cache, on la retourne au client
  .then(function(response)
    {
      return response;
    })
  // la donnée n'est pas disponible en cache, on tente de la récupérer sur le web
  .catch(function()
    {
      return fetch(event.request)
      // La donnée est disponible sur le web
      .then(function(response)
        {
          return caches.open(versionapplication)
          // On profite de sa disponibilité afin de l'enregistrer en cache et on la retourne au client
          .then(function(cache)
            {
              cache.put(event.request, response.clone());
              return response;
            });
        })
      // le web n'est pas disponible, on récupère la donnée par défaut du cache
      //.catch(function() { return caches.match('application.txt'); });
      .catch(function() { return caches.match('index.html'); });
    });

  event.respondWith(cachedResponse);
});

self.addEventListener('activate', function(event) {
  var cacheWhitelist = [versionapplication];

  event.waitUntil(
    caches.keys().then(function(keyList) {
      return Promise.all(keyList.map(function(key) {
        if (cacheWhitelist.indexOf(key) === -1) {
          return caches.delete(key);
        }
      }));
    })
  );
});
