//
// Created by drouar_b on 12/2/16.
//

#include <Core/BoardEvaluator.hh>
#include <Helpers/Stopwatch.hh>
#include "AI/NodeCache.hh"

#define SIMULATION_MAX_DEPTH 361

AI::NodeCache::NodeCache(Core::IReferee *referee) : work(ioService), running(false), rootRound(0),
                                                    root(new TreeNode(referee->clone(), WHITE)) {
    root->getReferee()->setPlayer(WHITE);
    for (int i = 0; i < THREADS_POOL; i++) {
        threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &ioService));
    }
    rng = boost::random::taus88(time(NULL));
}

AI::NodeCache::~NodeCache() {
    this->stop();
    delete (root);
}

void AI::NodeCache::threadTask(int threadId) {
    TreeNode *c;
    if ((c = root->getSimulationNode())) {
        simulate(c);
    }
    if (running)
        ioService.post(boost::bind(&AI::NodeCache::threadTask, this, threadId));
    else
        threadLocks[threadId].unlock();
}

void AI::NodeCache::run() {
    if (running)
        return;
    running = true;
    for (int i = 0; i < THREADS_POOL; i++) {
        threadLocks[i].lock();
        ioService.post(boost::bind(&AI::NodeCache::threadTask, this, i));
    }
}

void AI::NodeCache::pause() {
    running = false;
    for (int i = 0; i < THREADS_POOL; i++) {
        threadLocks[i].lock();
        threadLocks[i].unlock();
    }
}

void AI::NodeCache::stop() {
    if (!running)
        return;
    running = false;
    ioService.stop();
    threadpool.join_all();
}

int AI::NodeCache::getMove(Core::IReferee *referee, unsigned int ms) {
    int action;
    Stopwatch sw;

    sw.set();
    std::cout << "Check player" << std::endl;
    if (referee->getPlayer() != root->getReferee()->getPlayer()) {
        std::cout << "Need jump !" << std::endl;
        pause();
        std::cout << referee->getLastMove() << std::endl;
        std::cout << setNewRoot(referee, referee->getLastMove());
        std::cout << " new root " << root->getMove() << std::endl;
        run();
    }

    //Take a break :)
    usleep((ms - sw.elapsedMs()) * 1000);
    pause();

    if (referee->getNbrPlay() == 0)
        action = 10 * XPBOARD + 10;
    else
        action = root->getBestAction();

    if (action != -1) {
        referee->tryPlay(action);
        setNewRoot(referee, action);
    } else {
        std::cout << "Catastrophe, PANIC BUTTON" << std::endl;
        while (!referee->tryPlay((rand(19) + 1) * XPBOARD + rand(19) + 1));
        setNewRoot(referee, referee->getLastMove());
    }
    run();
    return action;
}

bool AI::NodeCache::setNewRoot(Core::IReferee *referee, int action) {
    bool found = false;
    TreeNode *oldRoot = root;

    for (auto &c : root->getChilds()) {
        if (c->getMove() == action) {
            c->setParent(NULL);
            root = c;
            c = NULL;
            found = true;
            break;
        }
    }
    if (root == oldRoot)
        root = new TreeNode(referee->clone(), referee->getPlayer());
    delete (oldRoot);
    return found;
}

void AI::NodeCache::simulate(AI::TreeNode *node) {
    Core::IReferee *sim = node->getReferee()->clone();

    int rc;
    int count = 0;
    std::vector<boardPos_t> *movesRand;
    std::vector<std::pair<boardPos_t, weight_t>> *moves;

    while (sim->getWinner() == NOPLAYER && count < SIMULATION_MAX_DEPTH) {
        /*if (count % SIM_RAND == 0) {
            rc = 0;
            movesRand = Core::BoardEvaluator::getInstance()->getAvailableMoves(sim);
            while (!sim->tryPlay((*movesRand)[randers[movesRand->size() - 1](rng)]) && ++rc < 361);
            if (rc == 360) {
                std::cout << "STOOOOP" << std::endl;
                node->backPropagate(0, NOPLAYER);
                return;
            }
            delete(movesRand);
        } else {*/
            moves = Core::BoardEvaluator::getInstance()->getInterestingMoves(sim);
            sim->tryPlay(moves->back().first);
            delete(moves);
        //}
        ++count;
    }
    node->backPropagate(1, sim->getWinner());
    delete (sim);
}

int AI::NodeCache::rand(int max) {
    return randers[max](rng);
}

AI::NodeCache *AI::NodeCache::getInstance(Core::IReferee *referee) {
    static NodeCache *cache = NULL;
    static int refereeId = -1;

    if (referee && refereeId != referee->getGameId()) {
        std::cout << "New nodecache" << (int)referee->getGameId() << std::endl;
        if (cache)
            delete (cache);
        cache = new NodeCache(referee);
        cache->run();
        refereeId = referee->getGameId();
    }
    return cache;
}

const std::array<boost::random::uniform_int_distribution<>, 361> AI::NodeCache::randers = {
        boost::random::uniform_int_distribution<>(0, 0),
        boost::random::uniform_int_distribution<>(0, 1),
        boost::random::uniform_int_distribution<>(0, 2),
        boost::random::uniform_int_distribution<>(0, 3),
        boost::random::uniform_int_distribution<>(0, 4),
        boost::random::uniform_int_distribution<>(0, 5),
        boost::random::uniform_int_distribution<>(0, 6),
        boost::random::uniform_int_distribution<>(0, 7),
        boost::random::uniform_int_distribution<>(0, 8),
        boost::random::uniform_int_distribution<>(0, 9),
        boost::random::uniform_int_distribution<>(0, 10),
        boost::random::uniform_int_distribution<>(0, 11),
        boost::random::uniform_int_distribution<>(0, 12),
        boost::random::uniform_int_distribution<>(0, 13),
        boost::random::uniform_int_distribution<>(0, 14),
        boost::random::uniform_int_distribution<>(0, 15),
        boost::random::uniform_int_distribution<>(0, 16),
        boost::random::uniform_int_distribution<>(0, 17),
        boost::random::uniform_int_distribution<>(0, 18),
        boost::random::uniform_int_distribution<>(0, 19),
        boost::random::uniform_int_distribution<>(0, 20),
        boost::random::uniform_int_distribution<>(0, 21),
        boost::random::uniform_int_distribution<>(0, 22),
        boost::random::uniform_int_distribution<>(0, 23),
        boost::random::uniform_int_distribution<>(0, 24),
        boost::random::uniform_int_distribution<>(0, 25),
        boost::random::uniform_int_distribution<>(0, 26),
        boost::random::uniform_int_distribution<>(0, 27),
        boost::random::uniform_int_distribution<>(0, 28),
        boost::random::uniform_int_distribution<>(0, 29),
        boost::random::uniform_int_distribution<>(0, 30),
        boost::random::uniform_int_distribution<>(0, 31),
        boost::random::uniform_int_distribution<>(0, 32),
        boost::random::uniform_int_distribution<>(0, 33),
        boost::random::uniform_int_distribution<>(0, 34),
        boost::random::uniform_int_distribution<>(0, 35),
        boost::random::uniform_int_distribution<>(0, 36),
        boost::random::uniform_int_distribution<>(0, 37),
        boost::random::uniform_int_distribution<>(0, 38),
        boost::random::uniform_int_distribution<>(0, 39),
        boost::random::uniform_int_distribution<>(0, 40),
        boost::random::uniform_int_distribution<>(0, 41),
        boost::random::uniform_int_distribution<>(0, 42),
        boost::random::uniform_int_distribution<>(0, 43),
        boost::random::uniform_int_distribution<>(0, 44),
        boost::random::uniform_int_distribution<>(0, 45),
        boost::random::uniform_int_distribution<>(0, 46),
        boost::random::uniform_int_distribution<>(0, 47),
        boost::random::uniform_int_distribution<>(0, 48),
        boost::random::uniform_int_distribution<>(0, 49),
        boost::random::uniform_int_distribution<>(0, 50),
        boost::random::uniform_int_distribution<>(0, 51),
        boost::random::uniform_int_distribution<>(0, 52),
        boost::random::uniform_int_distribution<>(0, 53),
        boost::random::uniform_int_distribution<>(0, 54),
        boost::random::uniform_int_distribution<>(0, 55),
        boost::random::uniform_int_distribution<>(0, 56),
        boost::random::uniform_int_distribution<>(0, 57),
        boost::random::uniform_int_distribution<>(0, 58),
        boost::random::uniform_int_distribution<>(0, 59),
        boost::random::uniform_int_distribution<>(0, 60),
        boost::random::uniform_int_distribution<>(0, 61),
        boost::random::uniform_int_distribution<>(0, 62),
        boost::random::uniform_int_distribution<>(0, 63),
        boost::random::uniform_int_distribution<>(0, 64),
        boost::random::uniform_int_distribution<>(0, 65),
        boost::random::uniform_int_distribution<>(0, 66),
        boost::random::uniform_int_distribution<>(0, 67),
        boost::random::uniform_int_distribution<>(0, 68),
        boost::random::uniform_int_distribution<>(0, 69),
        boost::random::uniform_int_distribution<>(0, 70),
        boost::random::uniform_int_distribution<>(0, 71),
        boost::random::uniform_int_distribution<>(0, 72),
        boost::random::uniform_int_distribution<>(0, 73),
        boost::random::uniform_int_distribution<>(0, 74),
        boost::random::uniform_int_distribution<>(0, 75),
        boost::random::uniform_int_distribution<>(0, 76),
        boost::random::uniform_int_distribution<>(0, 77),
        boost::random::uniform_int_distribution<>(0, 78),
        boost::random::uniform_int_distribution<>(0, 79),
        boost::random::uniform_int_distribution<>(0, 80),
        boost::random::uniform_int_distribution<>(0, 81),
        boost::random::uniform_int_distribution<>(0, 82),
        boost::random::uniform_int_distribution<>(0, 83),
        boost::random::uniform_int_distribution<>(0, 84),
        boost::random::uniform_int_distribution<>(0, 85),
        boost::random::uniform_int_distribution<>(0, 86),
        boost::random::uniform_int_distribution<>(0, 87),
        boost::random::uniform_int_distribution<>(0, 88),
        boost::random::uniform_int_distribution<>(0, 89),
        boost::random::uniform_int_distribution<>(0, 90),
        boost::random::uniform_int_distribution<>(0, 91),
        boost::random::uniform_int_distribution<>(0, 92),
        boost::random::uniform_int_distribution<>(0, 93),
        boost::random::uniform_int_distribution<>(0, 94),
        boost::random::uniform_int_distribution<>(0, 95),
        boost::random::uniform_int_distribution<>(0, 96),
        boost::random::uniform_int_distribution<>(0, 97),
        boost::random::uniform_int_distribution<>(0, 98),
        boost::random::uniform_int_distribution<>(0, 99),
        boost::random::uniform_int_distribution<>(0, 100),
        boost::random::uniform_int_distribution<>(0, 101),
        boost::random::uniform_int_distribution<>(0, 102),
        boost::random::uniform_int_distribution<>(0, 103),
        boost::random::uniform_int_distribution<>(0, 104),
        boost::random::uniform_int_distribution<>(0, 105),
        boost::random::uniform_int_distribution<>(0, 106),
        boost::random::uniform_int_distribution<>(0, 107),
        boost::random::uniform_int_distribution<>(0, 108),
        boost::random::uniform_int_distribution<>(0, 109),
        boost::random::uniform_int_distribution<>(0, 110),
        boost::random::uniform_int_distribution<>(0, 111),
        boost::random::uniform_int_distribution<>(0, 112),
        boost::random::uniform_int_distribution<>(0, 113),
        boost::random::uniform_int_distribution<>(0, 114),
        boost::random::uniform_int_distribution<>(0, 115),
        boost::random::uniform_int_distribution<>(0, 116),
        boost::random::uniform_int_distribution<>(0, 117),
        boost::random::uniform_int_distribution<>(0, 118),
        boost::random::uniform_int_distribution<>(0, 119),
        boost::random::uniform_int_distribution<>(0, 120),
        boost::random::uniform_int_distribution<>(0, 121),
        boost::random::uniform_int_distribution<>(0, 122),
        boost::random::uniform_int_distribution<>(0, 123),
        boost::random::uniform_int_distribution<>(0, 124),
        boost::random::uniform_int_distribution<>(0, 125),
        boost::random::uniform_int_distribution<>(0, 126),
        boost::random::uniform_int_distribution<>(0, 127),
        boost::random::uniform_int_distribution<>(0, 128),
        boost::random::uniform_int_distribution<>(0, 129),
        boost::random::uniform_int_distribution<>(0, 130),
        boost::random::uniform_int_distribution<>(0, 131),
        boost::random::uniform_int_distribution<>(0, 132),
        boost::random::uniform_int_distribution<>(0, 133),
        boost::random::uniform_int_distribution<>(0, 134),
        boost::random::uniform_int_distribution<>(0, 135),
        boost::random::uniform_int_distribution<>(0, 136),
        boost::random::uniform_int_distribution<>(0, 137),
        boost::random::uniform_int_distribution<>(0, 138),
        boost::random::uniform_int_distribution<>(0, 139),
        boost::random::uniform_int_distribution<>(0, 140),
        boost::random::uniform_int_distribution<>(0, 141),
        boost::random::uniform_int_distribution<>(0, 142),
        boost::random::uniform_int_distribution<>(0, 143),
        boost::random::uniform_int_distribution<>(0, 144),
        boost::random::uniform_int_distribution<>(0, 145),
        boost::random::uniform_int_distribution<>(0, 146),
        boost::random::uniform_int_distribution<>(0, 147),
        boost::random::uniform_int_distribution<>(0, 148),
        boost::random::uniform_int_distribution<>(0, 149),
        boost::random::uniform_int_distribution<>(0, 150),
        boost::random::uniform_int_distribution<>(0, 151),
        boost::random::uniform_int_distribution<>(0, 152),
        boost::random::uniform_int_distribution<>(0, 153),
        boost::random::uniform_int_distribution<>(0, 154),
        boost::random::uniform_int_distribution<>(0, 155),
        boost::random::uniform_int_distribution<>(0, 156),
        boost::random::uniform_int_distribution<>(0, 157),
        boost::random::uniform_int_distribution<>(0, 158),
        boost::random::uniform_int_distribution<>(0, 159),
        boost::random::uniform_int_distribution<>(0, 160),
        boost::random::uniform_int_distribution<>(0, 161),
        boost::random::uniform_int_distribution<>(0, 162),
        boost::random::uniform_int_distribution<>(0, 163),
        boost::random::uniform_int_distribution<>(0, 164),
        boost::random::uniform_int_distribution<>(0, 165),
        boost::random::uniform_int_distribution<>(0, 166),
        boost::random::uniform_int_distribution<>(0, 167),
        boost::random::uniform_int_distribution<>(0, 168),
        boost::random::uniform_int_distribution<>(0, 169),
        boost::random::uniform_int_distribution<>(0, 170),
        boost::random::uniform_int_distribution<>(0, 171),
        boost::random::uniform_int_distribution<>(0, 172),
        boost::random::uniform_int_distribution<>(0, 173),
        boost::random::uniform_int_distribution<>(0, 174),
        boost::random::uniform_int_distribution<>(0, 175),
        boost::random::uniform_int_distribution<>(0, 176),
        boost::random::uniform_int_distribution<>(0, 177),
        boost::random::uniform_int_distribution<>(0, 178),
        boost::random::uniform_int_distribution<>(0, 179),
        boost::random::uniform_int_distribution<>(0, 180),
        boost::random::uniform_int_distribution<>(0, 181),
        boost::random::uniform_int_distribution<>(0, 182),
        boost::random::uniform_int_distribution<>(0, 183),
        boost::random::uniform_int_distribution<>(0, 184),
        boost::random::uniform_int_distribution<>(0, 185),
        boost::random::uniform_int_distribution<>(0, 186),
        boost::random::uniform_int_distribution<>(0, 187),
        boost::random::uniform_int_distribution<>(0, 188),
        boost::random::uniform_int_distribution<>(0, 189),
        boost::random::uniform_int_distribution<>(0, 190),
        boost::random::uniform_int_distribution<>(0, 191),
        boost::random::uniform_int_distribution<>(0, 192),
        boost::random::uniform_int_distribution<>(0, 193),
        boost::random::uniform_int_distribution<>(0, 194),
        boost::random::uniform_int_distribution<>(0, 195),
        boost::random::uniform_int_distribution<>(0, 196),
        boost::random::uniform_int_distribution<>(0, 197),
        boost::random::uniform_int_distribution<>(0, 198),
        boost::random::uniform_int_distribution<>(0, 199),
        boost::random::uniform_int_distribution<>(0, 200),
        boost::random::uniform_int_distribution<>(0, 201),
        boost::random::uniform_int_distribution<>(0, 202),
        boost::random::uniform_int_distribution<>(0, 203),
        boost::random::uniform_int_distribution<>(0, 204),
        boost::random::uniform_int_distribution<>(0, 205),
        boost::random::uniform_int_distribution<>(0, 206),
        boost::random::uniform_int_distribution<>(0, 207),
        boost::random::uniform_int_distribution<>(0, 208),
        boost::random::uniform_int_distribution<>(0, 209),
        boost::random::uniform_int_distribution<>(0, 210),
        boost::random::uniform_int_distribution<>(0, 211),
        boost::random::uniform_int_distribution<>(0, 212),
        boost::random::uniform_int_distribution<>(0, 213),
        boost::random::uniform_int_distribution<>(0, 214),
        boost::random::uniform_int_distribution<>(0, 215),
        boost::random::uniform_int_distribution<>(0, 216),
        boost::random::uniform_int_distribution<>(0, 217),
        boost::random::uniform_int_distribution<>(0, 218),
        boost::random::uniform_int_distribution<>(0, 219),
        boost::random::uniform_int_distribution<>(0, 220),
        boost::random::uniform_int_distribution<>(0, 221),
        boost::random::uniform_int_distribution<>(0, 222),
        boost::random::uniform_int_distribution<>(0, 223),
        boost::random::uniform_int_distribution<>(0, 224),
        boost::random::uniform_int_distribution<>(0, 225),
        boost::random::uniform_int_distribution<>(0, 226),
        boost::random::uniform_int_distribution<>(0, 227),
        boost::random::uniform_int_distribution<>(0, 228),
        boost::random::uniform_int_distribution<>(0, 229),
        boost::random::uniform_int_distribution<>(0, 230),
        boost::random::uniform_int_distribution<>(0, 231),
        boost::random::uniform_int_distribution<>(0, 232),
        boost::random::uniform_int_distribution<>(0, 233),
        boost::random::uniform_int_distribution<>(0, 234),
        boost::random::uniform_int_distribution<>(0, 235),
        boost::random::uniform_int_distribution<>(0, 236),
        boost::random::uniform_int_distribution<>(0, 237),
        boost::random::uniform_int_distribution<>(0, 238),
        boost::random::uniform_int_distribution<>(0, 239),
        boost::random::uniform_int_distribution<>(0, 240),
        boost::random::uniform_int_distribution<>(0, 241),
        boost::random::uniform_int_distribution<>(0, 242),
        boost::random::uniform_int_distribution<>(0, 243),
        boost::random::uniform_int_distribution<>(0, 244),
        boost::random::uniform_int_distribution<>(0, 245),
        boost::random::uniform_int_distribution<>(0, 246),
        boost::random::uniform_int_distribution<>(0, 247),
        boost::random::uniform_int_distribution<>(0, 248),
        boost::random::uniform_int_distribution<>(0, 249),
        boost::random::uniform_int_distribution<>(0, 250),
        boost::random::uniform_int_distribution<>(0, 251),
        boost::random::uniform_int_distribution<>(0, 252),
        boost::random::uniform_int_distribution<>(0, 253),
        boost::random::uniform_int_distribution<>(0, 254),
        boost::random::uniform_int_distribution<>(0, 255),
        boost::random::uniform_int_distribution<>(0, 256),
        boost::random::uniform_int_distribution<>(0, 257),
        boost::random::uniform_int_distribution<>(0, 258),
        boost::random::uniform_int_distribution<>(0, 259),
        boost::random::uniform_int_distribution<>(0, 260),
        boost::random::uniform_int_distribution<>(0, 261),
        boost::random::uniform_int_distribution<>(0, 262),
        boost::random::uniform_int_distribution<>(0, 263),
        boost::random::uniform_int_distribution<>(0, 264),
        boost::random::uniform_int_distribution<>(0, 265),
        boost::random::uniform_int_distribution<>(0, 266),
        boost::random::uniform_int_distribution<>(0, 267),
        boost::random::uniform_int_distribution<>(0, 268),
        boost::random::uniform_int_distribution<>(0, 269),
        boost::random::uniform_int_distribution<>(0, 270),
        boost::random::uniform_int_distribution<>(0, 271),
        boost::random::uniform_int_distribution<>(0, 272),
        boost::random::uniform_int_distribution<>(0, 273),
        boost::random::uniform_int_distribution<>(0, 274),
        boost::random::uniform_int_distribution<>(0, 275),
        boost::random::uniform_int_distribution<>(0, 276),
        boost::random::uniform_int_distribution<>(0, 277),
        boost::random::uniform_int_distribution<>(0, 278),
        boost::random::uniform_int_distribution<>(0, 279),
        boost::random::uniform_int_distribution<>(0, 280),
        boost::random::uniform_int_distribution<>(0, 281),
        boost::random::uniform_int_distribution<>(0, 282),
        boost::random::uniform_int_distribution<>(0, 283),
        boost::random::uniform_int_distribution<>(0, 284),
        boost::random::uniform_int_distribution<>(0, 285),
        boost::random::uniform_int_distribution<>(0, 286),
        boost::random::uniform_int_distribution<>(0, 287),
        boost::random::uniform_int_distribution<>(0, 288),
        boost::random::uniform_int_distribution<>(0, 289),
        boost::random::uniform_int_distribution<>(0, 290),
        boost::random::uniform_int_distribution<>(0, 291),
        boost::random::uniform_int_distribution<>(0, 292),
        boost::random::uniform_int_distribution<>(0, 293),
        boost::random::uniform_int_distribution<>(0, 294),
        boost::random::uniform_int_distribution<>(0, 295),
        boost::random::uniform_int_distribution<>(0, 296),
        boost::random::uniform_int_distribution<>(0, 297),
        boost::random::uniform_int_distribution<>(0, 298),
        boost::random::uniform_int_distribution<>(0, 299),
        boost::random::uniform_int_distribution<>(0, 300),
        boost::random::uniform_int_distribution<>(0, 301),
        boost::random::uniform_int_distribution<>(0, 302),
        boost::random::uniform_int_distribution<>(0, 303),
        boost::random::uniform_int_distribution<>(0, 304),
        boost::random::uniform_int_distribution<>(0, 305),
        boost::random::uniform_int_distribution<>(0, 306),
        boost::random::uniform_int_distribution<>(0, 307),
        boost::random::uniform_int_distribution<>(0, 308),
        boost::random::uniform_int_distribution<>(0, 309),
        boost::random::uniform_int_distribution<>(0, 310),
        boost::random::uniform_int_distribution<>(0, 311),
        boost::random::uniform_int_distribution<>(0, 312),
        boost::random::uniform_int_distribution<>(0, 313),
        boost::random::uniform_int_distribution<>(0, 314),
        boost::random::uniform_int_distribution<>(0, 315),
        boost::random::uniform_int_distribution<>(0, 316),
        boost::random::uniform_int_distribution<>(0, 317),
        boost::random::uniform_int_distribution<>(0, 318),
        boost::random::uniform_int_distribution<>(0, 319),
        boost::random::uniform_int_distribution<>(0, 320),
        boost::random::uniform_int_distribution<>(0, 321),
        boost::random::uniform_int_distribution<>(0, 322),
        boost::random::uniform_int_distribution<>(0, 323),
        boost::random::uniform_int_distribution<>(0, 324),
        boost::random::uniform_int_distribution<>(0, 325),
        boost::random::uniform_int_distribution<>(0, 326),
        boost::random::uniform_int_distribution<>(0, 327),
        boost::random::uniform_int_distribution<>(0, 328),
        boost::random::uniform_int_distribution<>(0, 329),
        boost::random::uniform_int_distribution<>(0, 330),
        boost::random::uniform_int_distribution<>(0, 331),
        boost::random::uniform_int_distribution<>(0, 332),
        boost::random::uniform_int_distribution<>(0, 333),
        boost::random::uniform_int_distribution<>(0, 334),
        boost::random::uniform_int_distribution<>(0, 335),
        boost::random::uniform_int_distribution<>(0, 336),
        boost::random::uniform_int_distribution<>(0, 337),
        boost::random::uniform_int_distribution<>(0, 338),
        boost::random::uniform_int_distribution<>(0, 339),
        boost::random::uniform_int_distribution<>(0, 340),
        boost::random::uniform_int_distribution<>(0, 341),
        boost::random::uniform_int_distribution<>(0, 342),
        boost::random::uniform_int_distribution<>(0, 343),
        boost::random::uniform_int_distribution<>(0, 344),
        boost::random::uniform_int_distribution<>(0, 345),
        boost::random::uniform_int_distribution<>(0, 346),
        boost::random::uniform_int_distribution<>(0, 347),
        boost::random::uniform_int_distribution<>(0, 348),
        boost::random::uniform_int_distribution<>(0, 349),
        boost::random::uniform_int_distribution<>(0, 350),
        boost::random::uniform_int_distribution<>(0, 351),
        boost::random::uniform_int_distribution<>(0, 352),
        boost::random::uniform_int_distribution<>(0, 353),
        boost::random::uniform_int_distribution<>(0, 354),
        boost::random::uniform_int_distribution<>(0, 355),
        boost::random::uniform_int_distribution<>(0, 356),
        boost::random::uniform_int_distribution<>(0, 357),
        boost::random::uniform_int_distribution<>(0, 358),
        boost::random::uniform_int_distribution<>(0, 359),
        boost::random::uniform_int_distribution<>(0, 360)
};
