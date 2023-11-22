package co.edu.uceva.pais_service.model.service;

import co.edu.uceva.pais_service.model.dao.IPaisDao;
import co.edu.uceva.pais_service.model.entities.Pais;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;


@Service
public class PaisServiceImpl implements IPaisService {

    @Autowired
    IPaisDao paisDao;

    @Override
    public void delete(Pais pais) {
        paisDao.delete(pais);
    }


    @Transactional(readOnly = true)
    @Override
    public List<Pais> findAll() {
        List<Pais> paises = (List<Pais>)paisDao.findAll();
        return paises;
    }

    @Override
    public Pais findById(Long id) {
        return (Pais) paisDao.findById(id).get();
    }

    @Override
    public Pais save(Pais pais) {
        return paisDao.save(pais);
    }
}
