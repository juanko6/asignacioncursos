package co.edu.uceva.pais_service.model.service;

import co.edu.uceva.pais_service.model.entities.Pais;

import java.util.List;

public interface IPaisService {
    void delete (Pais pais);
    List<Pais> findAll(); //Devuelve una lista con todos los paises

    Pais findById(Long id);
    Pais save(Pais pais); //Guardo un pais y me retorna el mismo pais pero con el id
}
